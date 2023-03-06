#pragma once
#include<iostream>
#include<string>
#include<sstream>
class BaseDataType
{
public:
    BaseDataType(const std::string& tableName)
        :_tableName(tableName)
    {

    }
    virtual ~BaseDataType() {};
    virtual std::ostream& outPut(std::ostream& out) const = 0;
    virtual std::string getTableName()const = 0;
    virtual void setFieldsInDb(std::stringstream& buffer, int counterFieldsDefinition) = 0;
    virtual std::stringstream getFieldFromClass(int field)const = 0;
    virtual int getCountTableFields()const = 0;
    virtual std::string getFieldName(int field)const = 0;
    //virtual std::string save()const = 0;
    friend std::ostream& operator <<(std::ostream& out, const BaseDataType* parent);
protected:
    std::string _tableName;
};
std::ostream& operator <<(std::ostream& out, const BaseDataType* parent)
{
    return parent->outPut(out);
}