#include <iostream>
#include <memory>

/////////////////////////////////////////////////////////////////////////////////////////////////////

class Strategy 
{
public:

    virtual ~Strategy() = default;

//  ------------------------------

    virtual void test() const = 0;
};

////////////////////////////////////////////

class Slow : public Strategy 
{ 
public: 
    
    void test() const override 
    { 
        std::cout << "Slow::test\n";
    } 
};

/////////////////////////////////////////////////////////////////////////////////////////////////////

class Fast : public Strategy 
{ 
public: 
    
    void test() const override 
    { 
        std::cout << "Fast::test\n";
    } 
};

/////////////////////////////////////////////////////////////////////////////////////////////////////

class Entity
{
public:

    Entity(Strategy & strategy) : m_strategy(strategy) {}

//  --------------------------------------------------------------

    void test() const
    { 
        m_strategy.test();
    }

private:
    
    Strategy & m_strategy;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    std::unique_ptr<Strategy> strategy = std::make_unique<Slow>();

    Entity entity(*strategy);
    
    entity.test();
}