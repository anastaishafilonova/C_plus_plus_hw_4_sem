#include <algorithm>
#include <cassert>
#include <cstddef>
#include <functional>
#include <numeric>
#include <utility>
#include <vector>
#include <ranges>

template <typename Iterator>
void sort_(Iterator left, Iterator right) {
	for (auto i = std::next(left); i < right; i = std::next(i)) {
		for (auto j = i; j > left; j = std::prev(j)) {
			if (*(std::prev(j)) > *j) {
                std::iter_swap(std::prev(j), j);
            }
		}
	}
}

template <typename Iterator>
void merge(Iterator left, Iterator middle, Iterator right) {
	std::vector<typename std::iterator_traits<Iterator>::value_type> buffer(std::distance(left, right), 0);

    auto i = left, j = middle;
    auto k = std::begin(buffer);
    while (i != middle && j != right) {
        if (*i <= *j) {
            *k = *i;
            i = std::next(i);
        }
        else {
            *k = *j;
            j = std::next(j);
        }
        k = std::next(k);
    }

    while (i != middle) {
        *k = *i;
        k = std::next(k);
        i = std::next(i);
    }

    while (j != right) {
        *k = *j;
        k = std::next(k);
        j = std::next(j);
    }

    std::copy(std::begin(buffer), std::end(buffer), left);
}

template <typename Iterator>
void split(Iterator left, Iterator right) {
	if (std::distance(right, left) <= 64) {
		sort_(left, right);
	}
	else {
		auto middle = std::next(left, std::distance(left,  right) / 2);
		
		split(left, middle);
		
		split(middle, right);

		merge(left, middle, right);
	}
}

template <typename Iterator>
void timsort(Iterator left, Iterator right) {
	split(left, right);
}


int main() {
	auto size = 1'000uz;

	std::vector < int > vector(size, 0);

	for (auto i = 0uz; i < size; ++i) {
		vector[i] = size - i;
	}

	timsort(std::begin(vector), std::end(vector));

	assert(std::ranges::is_sorted(vector));
}
