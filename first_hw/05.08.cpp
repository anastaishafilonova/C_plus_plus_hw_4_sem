#include <iostream>
#include <memory>

///////////////////////////////////////////////////////////////////////////////////////////////////////

class Entity 
{
public:

    virtual ~Entity() = default;

//  ------------------------------

    virtual void test() const = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////

class Client : public Entity 
{ 
public: 
    
    void test() const override 
    { 
        std::cout << "Client::test\n";
    } 
};

////////////////////////////////////////////////////////////

class Server : public Entity 
{ 
public: 
    
    void test() const override 
    { 
        std::cout << "Server::test\n";
    } 
};

///////////////////////////////////////////////////////////////////////////////////////////////////////

class Decorator : public Entity
{
public:

    Decorator(Entity & entity): m_entity(entity) {}

//  -----------------------------------------------

    void test() const override
    { 
        std::cout << "Decorator::test : ";
        
        m_entity.test();
    }

private:

    Entity & m_entity;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    std::unique_ptr<Entity> entity_1 = std::make_unique<Client>();

    std::unique_ptr<Entity> entity_2 = std::make_unique<Decorator>(Decorator(*entity_1));

    entity_1->test();

    entity_2->test();
}