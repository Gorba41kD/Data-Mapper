#pragma once
#include<iostream>
#include"feature.h"
class Passport
{
private:
    int _serialNumber;
    std::string _registration;
public:
    int getSerialNumber()const
    {
        return _serialNumber;
    }
    std::string getRegistration()const
    {
        return _registration;
    }
    friend std::istream& operator >>(std::istream& ist, Passport& passport);
};