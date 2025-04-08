#include <iostream>
#include <memory>
#include <unordered_map>
#include <functional>

class Product {
public:
    virtual void test() const = 0;
    virtual ~Product() = default;
};

class ProductA : public Product {
public:
    void test() const override {
        std::cout << "ProductA" << std::endl;
    }
};

class ProductB : public Product {
public:
    void test() const override {
        std::cout << "ProductB" << std::endl;
    }
};

class Factory {
private:
    std::unordered_map<std::string, std::function<std::unique_ptr<Product>()>> factory;

public:
    void addProduct(const std::string& type, std::function<std::unique_ptr<Product>()> creator) {
        factory[type] = std::move(creator);
    }

    std::unique_ptr<Product> createProduct(const std::string& type) const {
        auto it = factory.find(type);
        if (it != factory.end()) {
            return it->second();
        }
        return nullptr;
    }
};

int main() {
    Factory factory;

    factory.addProduct("A", []() { return std::make_unique<ProductA>(); });
    factory.addProduct("B", []() { return std::make_unique<ProductB>(); });

    auto product1 = factory.createProduct("A");
    auto product2 = factory.createProduct("B");

    if (product1) product1->test();
    if (product2) product2->test();
}