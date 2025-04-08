#include <iostream>
#include <vector>
#include <limits>

int main() {
    std::vector<int> vec;

    std::cout << "Initial capacity = " << vec.capacity() << "\n";
    vec.push_back(0);
    auto prev_capacity = vec.capacity();
    for (ssize_t i = 1; i < 1000; ++i) {
        vec.push_back(i);
        if (vec.capacity() != prev_capacity) {
            std::cout << "Capacity before insertion = " << prev_capacity << "\n";
            std::cout << "Capacity after insertion = " << vec.capacity() << "\n";
            std::cout << "Coefficient of increasing capacity is " << (vec.capacity() / prev_capacity) << "\n";
            // the capacity of vector allways increase in 2 times
            std::cout << "\n";
            prev_capacity = vec.capacity();
        }
    }

    std::cout << "Capacity before reservation = " << vec.capacity() << "\n";
    auto size_before = vec.size();
    vec.reserve(2000);  // capacity of vector will equal 100 elements
    std::cout << "Capacity after reservation = " << vec.capacity() << "\n";
    for (ssize_t i = 1001; i < 1001 + vec.capacity() - size_before; ++i) {
        vec.push_back(i);
    }
    std::cout << "Capacity = " << vec.capacity() << " Size = " << vec.size() << "\n";
    vec.push_back(787886);
    std::cout << "Capacity after another one insertion = " << vec.capacity() << "\n";  // increased in 2 times

    try {
        vec.reserve(std::numeric_limits<size_t>::max() / 16); // allocate too much memory for vector
    } catch (const std::bad_alloc &e) {
        std::cout << "Error " << e.what() << '\n';
    }
}