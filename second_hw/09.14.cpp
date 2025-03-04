#include <iostream>
#include <iterator>

class OddNumberIterator {
public:
    using iterator_category = std::forward_iterator_tag;

    OddNumberIterator(int start = 1) : current(start) {
        if (current % 2 == 0) ++current;
    }

    int operator*() const { return current; }

    OddNumberIterator& operator++() {
        current += 2;
        return *this;
    }

    OddNumberIterator operator++(int) {
        OddNumberIterator temp = *this;
        ++(*this);
        return temp;
    }

    friend bool operator==(const OddNumberIterator& lhs, const OddNumberIterator& rhs) {
        return lhs.current == rhs.current;
    }

    friend bool operator!=(const OddNumberIterator& lhs, const OddNumberIterator& rhs) {
        return !(lhs == rhs);
    }

private:
    int current;
};

class OddNumberRange {
public:
    OddNumberRange(int start, int end) : start_(start), end_(end) {}

    OddNumberIterator begin() const { return OddNumberIterator(start_); }
    OddNumberIterator end() const { return OddNumberIterator(end_); }

private:
    int start_, end_;
};

int main() {
    OddNumberRange odd_numbers(7, 21);

    for (auto n : odd_numbers) {
        std::cout << n << " ";
    }
}
