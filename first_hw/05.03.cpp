#include <iostream>
#include <memory>

///////////////////////////////////////////////////////////////////////////////////

class Entity
{    
public:

    virtual ~Entity() = default;

//  ----------------------------------

    virtual std::shared_ptr<Entity> copy() const = 0;

    virtual void     test() const = 0;
};

///////////////////////////////////////////////////////////////////////////////////

class Client : public Entity
{
public:

    std::shared_ptr<Entity> copy() const override 
    { 
        return std::make_shared<Client>(Client(*this));
    } 

    void test() const override 
    { 
        std::cout << "Client::test\n";
    }
};

///////////////////////////////////////////////////////////////////////////////////

class Server : public Entity
{
public:

    std::shared_ptr<Entity> copy() const override 
    { 
        return std::make_shared<Server>(Server(*this));
    } 

    void test() const override 
    { 
        std::cout << "Server::test\n";
    }
};

///////////////////////////////////////////////////////////////////////////////////

class Factory
{
public:

    static auto make_client() { static Client prototype; return prototype.copy(); }
    
    static auto make_server() { static Server prototype; return prototype.copy(); }
};

///////////////////////////////////////////////////////////////////////////////////

int main()
{
    auto entity = Factory::make_client();

    entity->test();
}