#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <list>

void ToLower(char* str, const size_t size) {
    for (size_t i = 0; i < size; ++i) {
        str[i] = std::tolower(str[i]);
    }
}

bool PrefixFunction(char* word, const size_t word_size, char* text, const size_t text_size) {
    std::vector<char> in{word_size + 1 + text_size, std::allocator<char>{}};
    for (size_t i = 0; i < word_size; ++i) {
        in.data()[i] = word[i];
    }
    word[word_size] = '\n';
    for (size_t i = 0; i < text_size; ++i) {
        in.data()[word_size + 1 + i] = text[i];
    }

    std::vector<size_t> prefix_values{in.size(), std::allocator<size_t>{}};

    for (size_t idx = 1; idx < in.size(); ++idx) {
        size_t next = prefix_values[idx - 1];
        while ((in[next] != in[idx]) && next > 0) {
            next = prefix_values[next - 1];
        }
        if (in[next] == in[idx]) {
            prefix_values[idx] = next + 1;
            if (prefix_values[idx] == word_size) {
                return true;
            }
        } else {
            prefix_values[idx] = 0;
        }
    }

    return false;
}

bool FindInText(char* word, const size_t word_size, std::string& text) {
    const size_t len = text.size();
    const size_t block_size = 1024;
    const size_t n_blocks = len / block_size + !!(len % block_size);

    for (size_t i = 0; i < n_blocks; ++i) {
        const size_t begin = i * block_size;
        const size_t count = (begin + block_size > len) ? len - begin : block_size;

        bool is_found = PrefixFunction(word, word_size, text.data() + begin, count);
        if (is_found) {
            return true;
        }
    }

    return false;
}

int main() {
    std::string in;
    std::getline(std::cin, in);

    std::string text;
    std::list<bool> result;

    while (!in.empty()) {
        auto type = in[0];
        char* word = in.data() + 2;

        ToLower(word, in.size() - 2);

        if (type == '?') {
            bool is_found = FindInText(word, in.size() - 2, text);
            result.emplace_back(is_found ? true : false);
        } else if (type == 'A') {
            text += word;
        }

        std::getline(std::cin, in);
    }

    for (auto& res : result) {
        std::cout << (res ? "YES" : "NO") << std::endl;
    }

    return 0;
}
