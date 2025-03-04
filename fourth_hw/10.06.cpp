#include <iostream>
#include <map>

int main() {
    std::map<int, std::string> myMap;
    myMap[1] = "one";
    myMap[2] = "two";
    
    auto it = myMap.find(1);
    if (it != myMap.end()) {
        int* keyPtr = const_cast<int*>(&it->first);
        *keyPtr = 3;
    }

    for (const auto& [key, value] : myMap) {
        std::cout << key << ": " << value << "\n";
    }
}
