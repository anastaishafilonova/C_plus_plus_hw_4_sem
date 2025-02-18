#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <cassert>

template <typename Iterator, typename T>
Iterator find(Iterator first, Iterator last, const T& x) {
    Iterator end = last;
    while (first != last) {
        auto middle = std::next(first, std::distance(first, last) / 2);

        if (*middle < x) {
            first = std::next(middle);
        } else {
            last = middle;
        }
    }
    return (*first == x) ? first : end;
}

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    auto it = find(vec.begin(), vec.end(), 3);
    assert(it != vec.end() && *it == 3);

    std::list<int> lst = {10, 20, 30, 40, 50};
    auto it2 = find(lst.begin(), lst.end(), 25);
    assert(it2 == lst.end());
}
