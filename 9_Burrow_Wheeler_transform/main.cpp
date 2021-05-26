#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <memory>

class Transformator {
    const std::string& in_;
    int size_;
    std::string bwt_;
    std::vector<int> suffix_array_;
    std::vector<std::vector<int>> classes_;

public:
    explicit Transformator(const std::string& in) : in_(in), size_(in_.size()) {
        bwt_ = in_;
        suffix_array_.resize(in_.size());
        classes_.resize(GetClassesSize());
        for (auto& item : classes_) {
            item.resize(in_.size());
        }
    }

    std::vector<int>& SuffixArray();
    std::string& BurrowsWheelerTransform();

private:
    void InitSuffixArray();
    int GetClassesSize();
    int InitClasses();
    void MainLoop(int n_classes);
};

void Transformator::InitSuffixArray() {
    const int alphabet_length = 'z' - 'a' + 1;
    const char first_letter = 'a';

    std::vector<int> scores{alphabet_length, std::allocator<int>{}};

    for (auto& item : in_) {
        ++scores[item - first_letter];
    }
    for (int i = 1; i < alphabet_length; ++i) {
        scores[i] += scores[i - 1];
    }
    for (int i = size_ - 1; i >= 0; --i) {
        const int idx = in_[i] - first_letter;
        --scores[idx];
        suffix_array_[scores[idx]] = i;
    }
}

int Transformator::GetClassesSize() {
    std::vector<int> sizes{in_.size() + 1, std::allocator<int>{}};

    sizes[0] = -1;
    for (int i = 1; i <= size_; ++i) {
        sizes[i] = sizes[i / 2] + 1;
    }

    return sizes[size_] + 1;
}

int Transformator::InitClasses() {
    int num_classes = 0;

    classes_[0][suffix_array_[0]] = 0;
    for (int i = 1; i < size_; ++i) {
        if (in_[suffix_array_[i]] != in_[suffix_array_[i - 1]]) {
            ++num_classes;
        }
        classes_[0][suffix_array_[i]] = num_classes;
    }

    return num_classes + 1;
}

void Transformator::MainLoop(int n_classes) {
    std::vector<int> buffer{in_.size(), std::allocator<int>{}};
    for (int iter = 0;; ++iter) {
        std::vector<int> scores(n_classes, 0);
        for (int i = 0; i < size_; ++i) {
            ++scores[classes_[iter][i]];
        }
        for (int i = 1; i < n_classes; ++i) {
            scores[i] += scores[i - 1];
        }

        const int shift = 1 << iter;
        buffer = suffix_array_;
        for (int i = size_ - 1; i >= 0; --i) {
            int idx = buffer[i] - shift;
            if (idx < 0) {
                idx += size_;
            }
            --scores[classes_[iter][idx]];
            suffix_array_[scores[classes_[iter][idx]]] = idx;
        }

        if (size_ <= 2 * shift) {
            break;
        }

        int local_n_classes = 0;

        classes_[iter + 1][suffix_array_[0]] = local_n_classes;
        for (int i = 1; i < size_; ++i) {
            const int current_idx = suffix_array_[i];
            const int prev_idx = suffix_array_[i - 1];
            const int shifted_current_idx = (current_idx + shift) % size_;
            const int shifted_prev_idx = (prev_idx + shift) % size_;

            if (classes_[iter][current_idx] != classes_[iter][prev_idx] ||
                classes_[iter][shifted_current_idx] != classes_[iter][shifted_prev_idx]) {
                ++local_n_classes;
            }
            classes_[iter + 1][current_idx] = local_n_classes;
        }

        n_classes = local_n_classes + 1;
    }
}

std::vector<int>& Transformator::SuffixArray() {
    InitSuffixArray();
    int n_classes = InitClasses();
    MainLoop(n_classes);

    return suffix_array_;
}

std::string& Transformator::BurrowsWheelerTransform() {
    SuffixArray();
    for (int i = 0; i < size_; ++i) {
        const int idx = (suffix_array_[i] > 0) ? suffix_array_[i] - 1 : size_ - 1;
        bwt_[i] = in_[idx];
    }

    return bwt_;
}

int main() {
    // abcacbabc - bcccaabba
    // cbcabcbabcabcab - bccccacaaabbbbb

    std::string in;
    std::cin >> in;

    Transformator transformator{in};
    std::cout << transformator.BurrowsWheelerTransform() << std::endl;

    return 0;
}
