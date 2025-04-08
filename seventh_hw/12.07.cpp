#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <cassert>

template <typename Iter>
std::string join_strings(Iter begin, Iter end, const char* const separator) {
    if (begin == end) return "";
    
    std::ostringstream os;
    os << *begin;
    
    for (Iter it = std::next(begin); it != end; ++it) {
        os << separator << *it;
    }
    
    return os.str();
}

template <typename C>
std::string join_strings(const C& container, const char* const separator) {
    return join_strings(std::begin(container), std::end(container), separator);
}

int main() {
    using namespace std::string_literals;
    
    std::vector<std::string> v1{ "this","is","an","example" };
    std::vector<std::string> v2{ "example" };
    std::vector<std::string> v3{};
    
    std::cout << join_strings(v1, " ") << "\n";
    std::cout << join_strings(v2, ":") << "\n";
    std::cout << join_strings(v3, ", ") << "\n";
}