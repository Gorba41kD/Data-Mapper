#pragma once
#include<map>
#include"../Mapper.Model/Passport.h"
#include"../Mapper.Model/Person.h"
class Information;
class Irepository
{
public:
    virtual void save(const Information& information) = 0;
    virtual void save(const Passport& passport) = 0;
    virtual void save(const Person& person) = 0;
    virtual std::map<int, AirLine> read() = 0;
    virtual void print() = 0;
    virtual void printInformation() = 0;
    virtual std::map<int, AirLine> get() const = 0;
    virtual ~Irepository() {};
};
