#include <iostream>
#include <memory>
#include <string>

struct Person : public std::enable_shared_from_this<Person> {
    std::string name = "Vasya";
    int age = 15;

    std::shared_ptr<std::string> getNamePtr() {
        return {shared_from_this(), &name};
    }

    std::shared_ptr<int> getAgePtr() {
        return {shared_from_this(), &age};
    }
};

int main() {
    std::shared_ptr<Person> person = std::make_shared<Person>();

    std::shared_ptr<std::string> ptrToName = person->getNamePtr();
    std::shared_ptr<int> ptrToAge = person->getAgePtr();

    std::cout << "Name: " << *ptrToName << "\n";
    std::cout << "Age: " << *ptrToAge << "\n";

    std::cout << "use_count before reset: " << person.use_count() << "\n";

    person.reset();

    std::cout << "use_count after reset: " << ptrToName.use_count() << "\n";

    std::cout << "Name (after person reset): " << *ptrToName << "\n";
    std::cout << "Age (after person reset): " << *ptrToAge << "\n";
}
