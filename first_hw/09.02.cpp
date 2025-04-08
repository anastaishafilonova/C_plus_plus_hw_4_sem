#include <iostream>
#include <source_location>

class Logger {
public:
    Logger(std::source_location location_info) : _location_info(location_info) {
        print_start();
    }
    
    ~Logger() {
        print_end();
    }

    void print_start() {
        std::cout << "The beginning of function " << _location_info.function_name() << "\n"; 
    }

    void print_end() {
        std::cout << "The end of function " << _location_info.function_name() << "\n"; 
    }

private:
    const std::source_location _location_info;
};


void f() {
    Logger logger(std::source_location::current());
    std::cout << "Hello from function f()\n";
}

int main() {
    f();
}
