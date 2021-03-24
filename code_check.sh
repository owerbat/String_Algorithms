echo "clang-format"
clang-format -i main.cpp
echo "clang-tidy"
clang-tidy main.cpp -- -std=c++17
