#include <iostream>
#include <vector>
#include <memory>

//////////////////////////////////////////////////////////////

class Observer 
{
public:

    virtual ~Observer() = default;

//  --------------------------------------

    virtual void test(int x) const = 0;
};

//////////////////////////////////////////////////////////////

class Entity 
{
public:

   ~Entity() {}

//  -------------------------------------------------------

    void add_observer(std::shared_ptr<Observer> observer) 
    { 
        m_observers.push_back(observer);
    }

    void set(int x) 
    { 
        m_data = x;
        
        notify_observers();
    }

    void notify_observers() const
    { 
        for (auto observer : m_observers)
        {
            if (observer) 
            {
                observer->test(m_data);
            }
        }
    }

private:

    int m_data = 0; 
    
    std::vector <std::shared_ptr<Observer>> m_observers;
};

//////////////////////////////////////////////////////////////

class Client : public Observer 
{
public:

    void test(int x) const override
    {
        std::cout << "Client::test : x = " << x << '\n';
    }
};

//////////////////////////////////////////////////////////////

class Server : public Observer
{
public:

    void test(int x) const override
    {
        std::cout << "Server::test : x = " << x << '\n';
    }
};

//////////////////////////////////////////////////////////////

int main() 
{
    Entity entity;

    entity.add_observer(std::shared_ptr<Client>());
    
    entity.add_observer(std::shared_ptr<Server>());
    
    entity.set(1);

    entity.set(2);
}