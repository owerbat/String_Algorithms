g++ main.cpp -std=c++17 -O2 -Wall -Werror -Wsign-compare -o fast
g++ main.cpp -fsanitize=address,undefined -fno-sanitize-recover=all -std=c++17 -O2 -Wall -Werror -Wsign-compare -o debug
