#include <string>
#include <iostream>


auto compress_string(std::string initial_string) {
    if (std::size(initial_string) == 0) {
        return std::string();
    }
    std::string result = "";
    result += initial_string[0];

    size_t count = 1;

    for (size_t i = 1; i < std::size(initial_string); ++i) {
        if (initial_string[i] == initial_string[i - 1]) {
            count++;
        } else {
            result += std::to_string(count);
            result += initial_string[i];
            count = 1;
        }
    }

    if (count != 0) {
        result += std::to_string(count);
    }

    return result;
}

int main() {
    std::cout << compress_string("aaabbcccd") << "\n";
    std::cout << compress_string("a") << "\n";
    std::cout << compress_string("") << "\n";
}