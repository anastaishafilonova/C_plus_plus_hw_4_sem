#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>
#include <random>
#include <functional>
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

auto generate_strings(int count, int length = 10) {
    std::set<std::string> strings;
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<char> distrib('a', 'z');

    for (; strings.size() < count;) {
        std::string str;
        for (ssize_t i = 0; i < length; ++i) {
            str += (distrib(gen));
        }
        strings.insert(str);
    }

    return strings;
}

uint32_t RSHash(const std::string& str) {
    uint32_t a = 63689, b = 378551, hash = 0;
    for (char c : str) {
        hash = hash * a + c;
        a *= b;
    }
    return hash;
}

uint32_t JSHash(const std::string& str) {
    uint32_t hash = 1315423911;
    for (char c : str) {
        hash ^= ((hash << 5) + c + (hash >> 2));
    }
    return hash;
}

uint32_t PJWHash(const std::string& str) {
    uint32_t hash = 0, high;
    for (char c : str) {
        hash = (hash << 4) + c;
        if ((high = hash & 0xF0000000)) hash ^= high >> 24;
        hash &= ~high;
    }
    return hash;
}

uint32_t ELFHash(const std::string& str) {
    uint32_t hash = 0, x;
    for (char c : str) {
        hash = (hash << 4) + c;
        if ((x = hash & 0xF0000000)) hash ^= x >> 24;
        hash &= ~x;
    }
    return hash;
}

uint32_t BKDRHash(const std::string& str) {
    uint32_t seed = 131, hash = 0;
    for (char c : str) hash = hash * seed + c;
    return hash;
}

uint32_t SDBMHash(const std::string& str) {
    uint32_t hash = 0;
    for (char c : str) hash = c + (hash << 6) + (hash << 16) - hash;
    return hash;
}

uint32_t DJBHash(const std::string& str) {
    uint32_t hash = 5381;
    for (char c : str) hash = ((hash << 5) + hash) + c;
    return hash;
}

uint32_t APHash(const std::string& str) {
    uint32_t hash = 0xAAAAAAAA;
    for (size_t i = 0; i < str.length(); i++) {
        hash ^= (i & 1) ? ((hash << 7) ^ str[i] * (hash >> 3)) : (~((hash << 11) + (str[i] ^ (hash >> 5))));
    }
    return hash;
}

uint32_t DEKHash(const std::string& str) {
    uint32_t hash = str.size();
    unsigned int i    = 0;
    for (char c : str) {
        hash = ((hash << 5) ^ (hash >> 27)) ^ c;
    }
    return hash;
}

auto test_collisions(std::string& func_name, 
                                 std::function<uint32_t(const std::string&)> hash_func, 
                                 const std::set<std::string>& strings, 
                                 const std::vector<int>& sizes) {
    std::vector<int> collisions_list;
    for (int size : sizes) {
        std::unordered_map<uint32_t, int> hash_counts;
        int total = 0;

        for (const auto& str : strings) {
            if (total++ >= size) break;
            hash_counts[hash_func(str)]++;
        }

        int collisions = size - hash_counts.size();
        collisions_list.push_back(collisions);
        std::cout << "Хеш-функция: " << func_name << " | Обработано: " << size << " строк | Коллизии: " << collisions << "\n";
    }
    return collisions_list;
}

int main() {
    std::vector<int> sizes;
    for (ssize_t i = 100000; i <= 2000000; i += 100000) {
        sizes.push_back(i);
    }

    auto strings = generate_strings(2000000);

    std::vector<std::pair<std::string, std::function<uint32_t(const std::string&)>>> hash_functions = {
        {"RSHash", RSHash}, {"JSHash", JSHash}, {"PJWHash", PJWHash}, {"ELFHash", ELFHash}, 
        {"BKDRHash", BKDRHash}, {"SDBMHash", SDBMHash}, {"DJBHash", DJBHash}, 
        {"APHash", APHash}, {"DEKHash", DEKHash}
    };

    plt::figure_size(1200, 600);

    u_int64_t i = 0;
    for (auto& [name, func] : hash_functions) {
        std::vector<int> collisions = test_collisions(name, func, strings, sizes);
        plt::plot(sizes, collisions, {{"label", name}});
    }

    plt::xlabel("Количество строк");
    plt::ylabel("Коллизии");
    plt::title("Количество коллизий для разных хэш-функций");
    plt::legend();
    plt::show();
}
