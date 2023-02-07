#pragma once
#include<iostream>
#include"../Mapper.Utility/feature.h"
class Person
{
private:
    std::string _name;
    std::string _surname;
public:
    std::string getName()const
    {
        return _name;
    }
    std::string getSurName()const
    {
        return _surname;
    }
    friend std::istream& operator >>(std::istream& ist, Person& person);
};

