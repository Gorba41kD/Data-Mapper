#pragma once
#include<memory>
#include"BaseDataType.h"
#include<map>
#include<vector>
template<typename T>
class IRepository
{
public:
    virtual std::map<int, std::shared_ptr<T>> readCollections(const std::vector<int>& fields) = 0;
    //virtual void save(const std::unique_ptr<T>& model) = 0;
    virtual void save(const std::unique_ptr<T>& model) = 0;
    virtual void readModel(std::unique_ptr<T>& model, const std::vector<int>& fields, int id = 1) = 0;
    virtual ~IRepository() {}
};