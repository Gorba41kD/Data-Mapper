#include <iostream>
#include "Models.hpp"

int main()
{
    using namespace Arch;
    try
    {
        ChannelModel model;
    }
    catch (const std::exception& exp)
    {
        std::cerr << exp.what() << std::endl;
    }
    

    return 0;
}
