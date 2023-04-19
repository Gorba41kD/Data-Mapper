#pragma once
template<typename T>
class ContainerOfModels
{
private:
    ContainerOfModels(const ContainerOfModels&) = delete;
    ContainerOfModels& operator=(ContainerOfModels&) = delete;
    ContainerOfModels(){ std::cout << "ContainerOfModels()" << std::endl; }
    std::map<int, std::shared_ptr<T>> _container;
public:
    static ContainerOfModels& getInstance() {
        static ContainerOfModels  instance;
        return instance;
    }
    void setContainer(std::map<int, std::shared_ptr<T>> container)
    {
        _container = container;
    }
    std::map<int, std::shared_ptr<T>> getMap()const
    {
        return _container;
    }
    void print()
    {
        for (auto it = _container.begin(); it != _container.end(); ++it)
        {
            std::cout << it->second;
        }
    }
    ~ContainerOfModels()
    {
        std::cout << "~ContainerOfModels()" << std::endl;
    }
};