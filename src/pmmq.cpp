#include <iostream>
#include <vector>
#include <string>

#include "Broker.hpp"

// Poor Man's Message Queue

int main()
{
    std::vector<std::string> msg {"Hello", "C++", "World", "from", "VS Code!"};

    for (const auto& w : msg)
    {
        std::cout << w << " ";
    }
    std::cout << std::endl;
    
    const auto xb1 = std::make_shared<Broker>();

    return 0;
}