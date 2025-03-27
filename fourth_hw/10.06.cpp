#include <iostream>
#include <map>

struct Key {
    mutable int value;
    Key(int v) : value(v) {}
    
    bool operator<(const Key& other) const {
        return value < other.value;
    }
};

void first_way() {
    std::map<int, std::string> myMap;
    myMap[1] = "one";
    myMap[2] = "two";

    std::cout << "Before changes:" << "\n";
    for (const auto& [key, value] : myMap) {
        std::cout << key << ": " << value << "\n";
    }
    
    auto it = myMap.find(1);
    if (it != myMap.end()) {
        int* keyPtr = const_cast<int*>(&it->first);
        *keyPtr = 3;
    }

    std::cout << "After changes:" << "\n";
    for (const auto& [key, value] : myMap) {
        std::cout << key << ": " << value << "\n";
    }
}

void second_way() {
    std::map<Key, std::string> myMap;
    myMap[Key(1)] = "one";
    myMap[Key(2)] = "two";

    std::cout << "Before changes:" << "\n";
    for (const auto& [key, value] : myMap) {
        std::cout << key.value << ": " << value << "\n";
    }
    
    auto it = myMap.find(1);
    if (it != myMap.end()) {
        it->first.value = 10;
    }

    std::cout << "After changes:" << "\n";
    for (const auto& [key, value] : myMap) {
        std::cout << key.value << ": " << value << "\n";
    }
}

int main() {
    first_way();
    second_way();
}