#include <iostream>
#include <string>
#include <vector>
#include <memory>

void Zfunction(const std::string& in, std::vector<int>& result) {
    const int size = in.size();
    result[0] = size;

    int left = 1, right = 1;
    for (int current = 1; current < size; ++current) {
        int distance = right - current;
        int ii = current - left;
        if (result[ii] < distance) {
            result[current] = result[ii];
        } else {
            distance = (distance >= 0) ? distance : 0;
            result[current] += distance;
            for (int k = current + distance; k < size; ++k) {
                if (in[k] == in[k - current]) {
                    ++result[current];
                } else {
                    break;
                }
            }
            left = current;
            right = current + result[current];
        }
    }
}

int main() {
    std::string in;
    std::cin >> in;

    std::vector<int> result{in.size(), std::allocator<int>{}};
    Zfunction(in, result);

    for (auto& value : result) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    return 0;
}
