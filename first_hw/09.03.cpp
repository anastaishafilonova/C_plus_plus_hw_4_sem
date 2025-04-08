#include <iostream>
#include <vector>

int x = 5; 

class ScopeGuard {
public:
    ScopeGuard() {}
    ~ScopeGuard() {
        if (!done_b) {
            x -= 5;
            std::cout << "x = " << x << "\n";
        }
    }

    void done() {
        done_b = true;
    }
private:
    bool done_b = false;
};

void a() {
    x += 5;
}

void b() {
    std::vector<int> v;
    std::cout << v.at(1000);
}

int main() {
    a();
    ScopeGuard s = ScopeGuard();
    try {
        b();
        s.done();
    } catch(const std::exception e) {
        std::cout << e.what() << "\n";
    }
}