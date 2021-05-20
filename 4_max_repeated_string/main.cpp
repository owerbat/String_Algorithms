#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

void PrefixFunction(const std::string& in, std::vector<size_t>& prefix_values) {
    prefix_values[0] = 0;

    for (size_t i = 1; i < in.size(); ++i) {
        size_t next = prefix_values[i - 1];
        while ((in[next] != in[i]) && next > 0) {
            next = prefix_values[next - 1];
        }
        if (in[next] == in[i]) {
            prefix_values[i] = next + 1;
        } else {
            prefix_values[i] = 0;
        }
    }
}

int main() {
    std::string in;
    std::cin >> in;

    size_t repeate_count = 1;
    const size_t size = in.size();
    for (size_t start_idx = 0; start_idx < size; ++start_idx) {
        const size_t local_size = size - start_idx;
        const std::string local_in = in.substr(start_idx, local_size);
        std::vector<size_t> prefix_function{local_size, std::allocator<size_t>{}};

        PrefixFunction(local_in, prefix_function);
        for (size_t i = 1; i < local_size; ++i) {
            const size_t prefix_length = i + 1;
            if ((prefix_length % (prefix_length - prefix_function[i])) == 0) {
                repeate_count =
                    std::max(repeate_count, prefix_length / (prefix_length - prefix_function[i]));
            }
        }
    }

    std::cout << repeate_count << std::endl;

    return 0;
}
