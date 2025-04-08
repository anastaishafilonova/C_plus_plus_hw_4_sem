#include <mutex>
#include <thread>
#include <iostream>
#include <vector>

std::vector<int> v;

std::mutex m;

void f() {
    std::lock_guard<std::mutex> lock(m);  // Обёртка над mutex, удовлетворяющая идиоме RAII
    for (size_t i = 0; i < 10; ++i) {
        v.push_back(i);
    }
}

/*
void f() {
    m.lock();  // если произойдёт какая-то ошибка и не вызовется unlock, то мы застрянем навечно  
    for (size_t i = 0; i < 10; ++i) {
        v.push_back(i);
    }
    m.unlock();
}
*/

int main() {
    std::thread t(f);
    f();
    t.join();
}
