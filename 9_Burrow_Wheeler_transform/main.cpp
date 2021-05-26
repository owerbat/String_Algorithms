#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>

using Uint = unsigned int;

struct Suffix {
    const std::string* str;
    Uint size;
    Uint idx;

    bool operator<(const Suffix& pair) const {
        for (Uint i = 0; i < size; ++i) {
            const Uint this_index = (idx + i) % size;
            const Uint pair_index = (pair.idx + i) % size;
            if ((*str)[this_index] != (*pair.str)[pair_index]) {
                return (*str)[this_index] < (*pair.str)[pair_index];
            }
        }
        return true;
    }
};

void SuffixArray(const std::string& in, std::vector<Uint>& suffix_array) {
    const Uint size = in.size();

    std::vector<Suffix> suffixes;
    for (Uint i = 0; i < size; ++i) {
        suffixes.emplace_back(Suffix{&in, size, i});
    }

    std::sort(suffixes.begin(), suffixes.end());

    for (Uint i = 0; i < size; ++i) {
        suffix_array[i] = suffixes[i].idx;
    }
}

void BurrowsWheelerTransform(const std::string& in, const std::vector<Uint>& suffix_array,
                             std::string& result) {
    const Uint size = suffix_array.size();
    for (Uint i = 0; i < size; ++i) {
        const Uint idx = (suffix_array[i] > 0) ? suffix_array[i] - 1 : size - 1;
        result[i] = in[idx];
    }
}

int main() {
    // abcacbabc - bcccaabba
    // cbcabcbabcabcab - bccccacaaabbbbb

    std::string in;
    std::cin >> in;

    std::vector<Uint> suffix_array{in.size(), std::allocator<Uint>{}};
    SuffixArray(in, suffix_array);

    std::string result{in};
    BurrowsWheelerTransform(in, suffix_array, result);
    std::cout << result << std::endl;

    return 0;
}
