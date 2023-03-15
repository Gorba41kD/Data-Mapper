#include <iostream>
#include "Models.hpp"
#include "Adapter.hpp"

int main()
{
    using namespace Arch;
    try
    {
        ChannelModel model;
        Adapter adapter;

        adapter.read(model, { ChannelFields::ID,ChannelFields::NAME });

        std::for_each(model[ChannelFields::ID].begin(), model[ChannelFields::ID].end(), [](const auto& id) {std::cout << "\nid: " << id << "."; });
    }
    catch (const std::exception& exp)
    {
        std::cerr << exp.what() << std::endl;
    }
    

    return 0;
}
