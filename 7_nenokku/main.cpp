#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <list>
#include <algorithm>
#include <execution>

struct WordPair {
    std::string& word;
    size_t idx;

    WordPair(std::string& word, size_t idx) : word(word), idx(idx) {
    }
};

void ToLower(std::string& str) {
    for (auto& s : str) {
        s = std::tolower(s);
    }
}

bool PrefixFunction(std::string& word, std::string& text) {
    std::string in = word + "\n" + text;
    std::vector<size_t> prefix_values{in.size(), std::allocator<size_t>{}};

    for (size_t idx = 1; idx < in.size(); ++idx) {
        size_t next = prefix_values[idx - 1];
        while ((in[next] != in[idx]) && next > 0) {
            next = prefix_values[next - 1];
        }
        if (in[next] == in[idx]) {
            prefix_values[idx] = next + 1;
            if (prefix_values[idx] == word.size()) {
                return true;
            }
        } else {
            prefix_values[idx] = 0;
        }
    }

    return false;
}

int main() {
    size_t idx = 0;
    std::list<WordPair> words;
    std::string in, text;
    std::getline(std::cin, in);

    while (!in.empty()) {
        auto type = in[0];
        auto word = in.substr(2, in.size() - 2);

        ToLower(word);

        if (type == '?') {
            WordPair word_pair{word, idx++};
            words.emplace_back(word_pair);
        } else if (type == 'A') {
            text += word;
        }
    }

    std::vector<bool> result{words.size(), std::allocator<bool>{}};

    std::for_each(std::execution::par, words.begin(), words.end(), [&](auto& word) {
        bool is_founded = PrefixFunction(word.word, text);
        result[word.idx] = is_founded ? true : false;
    });

    for (auto& res : result) {
        std::cout << (res ? "YES" : "NO") << std::endl;
    }

    return 0;
}
