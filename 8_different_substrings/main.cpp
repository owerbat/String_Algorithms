#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

size_t PrefixFunction(const size_t size, const std::string& in,
                      std::vector<size_t>& prefix_values) {
    size_t max = 0;
    prefix_values[0] = 0;

    for (size_t i = 1; i < size; ++i) {
        size_t next = prefix_values[i - 1];
        while ((in[size - 1 - next] != in[size - 1 - i]) && next > 0) {
            next = prefix_values[next - 1];
        }
        if (in[size - 1 - next] == in[size - 1 - i]) {
            prefix_values[i] = next + 1;
        } else {
            prefix_values[i] = 0;
        }
        max = std::max(max, prefix_values[i]);
    }

    return max;
}

int main() {
    std::string in;
    std::cin >> in;

    size_t n_substrings = 1;
    const size_t size = in.size();

    for (size_t local_size = 2; local_size <= size; ++local_size) {
        std::vector<size_t> prefix_function{local_size, std::allocator<size_t>{}};
        const size_t local_max = PrefixFunction(local_size, in, prefix_function);

        n_substrings += local_size - local_max;
    }

    std::cout << n_substrings << std::endl;

    return 0;
}
