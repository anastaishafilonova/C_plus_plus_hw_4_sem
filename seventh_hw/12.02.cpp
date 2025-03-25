#include <iostream>
#include <string>
#include <chrono>


bool is_sso(const std::string& s) {
    //  Проверяем, что адрес данных строки находится внутри объекта
    return reinterpret_cast<const void*>(s.data()) >= reinterpret_cast<const void*>(&s) &&
           reinterpret_cast<const void*>(s.data()) <= reinterpret_cast<const void*>(&s + 1);
}

size_t find_buffer_sso_size() {
    std::string s;
    size_t max_ssize = 0;
    for (size_t i = 1; i < 100; ++i) {
        s.assign(i, 'x');
        if (is_sso(s)) {
            max_ssize = i;
        } else {
            break;
        }
    }
    return max_ssize;
}


int main() {
    int N = find_buffer_sso_size();
    const size_t iterations = 10'000'000;
    
    // Создание строк с SSO
    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < iterations; ++i) {
        std::string s(N, 'x');
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration_sso = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    
    // Создание строк без SSO
    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < iterations; ++i) {
        std::string s(N + 1, 'x');
    }
    end = std::chrono::high_resolution_clock::now();
    auto duration_no_sso = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    
    std::cout << "SSO (N=" << N << "): " << duration_sso << " ms\n";
    std::cout << "Динамическая (N+1): " << duration_no_sso << " ms\n";
}