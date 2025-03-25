// Алгоритмы Бойера-Мура и Бойера-Мура-Хорспула

#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <chrono>


auto boyer_moore(const std::string& text, const std::string& pattern) {
    auto searcher = std::boyer_moore_searcher(pattern.begin(), pattern.end());
    auto it = std::search(text.begin(), text.end(), searcher);
    return it;
}

auto horspool(const std::string& text, const std::string& pattern) {
    auto searcher = std::boyer_moore_horspool_searcher(pattern.begin(), pattern.end());
    auto it = std::search(text.begin(), text.end(), searcher);
    return it;
}

auto default_search(const std::string& text, const std::string& pattern) {
    size_t pos = text.find(pattern);
    return pos;
}

void benchmark_search(const std::string& text, const std::string& pattern) {
    auto start = std::chrono::high_resolution_clock::now();
    auto searcher_bm = std::boyer_moore_searcher(pattern.begin(), pattern.end());
    auto it_bm = std::search(text.begin(), text.end(), searcher_bm);
    auto end_bm = std::chrono::high_resolution_clock::now();

    auto searcher_horspool = std::boyer_moore_horspool_searcher(pattern.begin(), pattern.end());
    auto it_hp = std::search(text.begin(), text.end(), searcher_horspool);
    auto end_hp = std::chrono::high_resolution_clock::now();

    auto it_default = text.find(pattern);
    auto end_default = std::chrono::high_resolution_clock::now();

    auto time_bm = std::chrono::duration_cast<std::chrono::microseconds>(end_bm - start).count();
    auto time_hp = std::chrono::duration_cast<std::chrono::microseconds>(end_hp - end_bm).count();
    auto time_default = std::chrono::duration_cast<std::chrono::microseconds>(end_default - end_hp).count();

    std::cout << "Boyer-Moore: " << time_bm << " мкс\n";
    std::cout << "Horspool: " << time_hp << " мкс\n";
    std::cout << "Default: " << time_default << " мкс\n";
}


int main() {
    std::string text(1'000'000, 'A');
    text += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string pattern = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    benchmark_search(text, pattern);
}
