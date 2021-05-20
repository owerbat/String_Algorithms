#include <iostream>
#include <string>
#include <vector>
#include <memory>

void PrefixFunction(std::string& in, std::vector<size_t>& prefix_values) {
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

    const size_t size = in.size();
    std::vector<size_t> prefix_function{size, std::allocator<size_t>{}};
    PrefixFunction(in, prefix_function);

    size_t period_length = 1;
    if ((size % (size - prefix_function[size - 1])) == 0) {
        period_length = size / (size - prefix_function[size - 1]);
    }
    std::cout << period_length << std::endl;

    return 0;
}
