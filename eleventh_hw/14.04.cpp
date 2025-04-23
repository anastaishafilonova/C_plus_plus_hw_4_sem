#include <algorithm>
#include <cassert>
#include <cmath>
#include <concepts>
#include <functional>
#include <iterator>
#include <numeric>
#include <ranges>
#include <thread>
#include <vector>
#include <chrono>
#include <iostream>

#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

template <std::ranges::view V, typename T>
class Task {
public:
    void operator()(V view, T &sum) const {
        for (auto val : view) {
            sum += std::log1p(std::abs(std::sin(val) * std::cos(val))) * std::pow(val, 0.5);
        }
    }
};

template <std::ranges::view V, typename T>
auto reduce(V view, T sum, unsigned int num_threads) {
    auto begin = std::begin(view), end = std::end(view);

    if (auto size = std::distance(begin, end); size > 0) {
        unsigned int concurrency = std::max(1u, num_threads);
        std::vector<T> sums(concurrency, T());
        auto step = size / concurrency;

        auto begin_block = begin;
        auto end_block = begin_block;
        
        {
        std::vector<std::jthread> threads;
        for (unsigned int i = 0; i < concurrency - 1; ++i) {
            end_block = std::next(begin_block, step);
            auto range = std::ranges::subrange(begin_block, end_block);
            threads.emplace_back(Task<decltype(range), T>(), range, std::ref(sums[i]));
            begin_block = end_block;
        }

        auto range = std::ranges::subrange(begin_block, end);
        Task<decltype(range), T>()(range, sums[concurrency - 1]);
        }
        sum = std::accumulate(sums.begin(), sums.end(), T());
    }
    return sum;
}

int main() {
    constexpr size_t data_size = 100000000;
    std::vector<double> data(data_size);
    std::iota(data.begin(), data.end(), 1.0);

    std::vector<int> thread_counts;
    std::vector<double> times;
    auto min_time = std::chrono::duration<double, std::milli>(20000.0);
    auto optimum = 1u;

    for (unsigned int threads = 1; threads <= std::thread::hardware_concurrency() * 15; ++threads) {
        auto start = std::chrono::high_resolution_clock::now();
        double result = reduce(std::ranges::views::all(data), 0.0, threads);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;
        if (elapsed < min_time - std::chrono::duration<double, std::milli>(100.0)) {
            optimum = threads;
            min_time = elapsed;
        }

        thread_counts.push_back(threads);
        times.push_back(elapsed.count());

        std::cout << "Threads: " << threads << ", Time: " << elapsed.count() << " ms, Result: " << result << '\n';
    }
    std::cout << "Optimal count of threads: " << optimum << "\n";

    plt::figure_size(1000, 800);
    plt::plot(thread_counts, times);
    plt::xlabel("Количество потоков");
    plt::ylabel("Время выполнения (мс)");
    plt::title("Зависимость времени от количества потоков");
    plt::grid(true);
    plt::show();
}