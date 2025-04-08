#include <iostream>
#include <cassert>

class FuncPtr_;
typedef FuncPtr_ (*FuncPtr)();

class FuncPtr_ {
    public:
    FuncPtr_(FuncPtr p): p_(p) {}
    operator FuncPtr() { return p_; }
    private:
    FuncPtr p_;
};

FuncPtr_ f() { return f; }

int main() {
    FuncPtr p = f();
    p();
}
