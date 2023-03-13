#pragma once
#include"BaseDataType.h"
class Person :public BaseDataType
{
private:
    int _id = 0;
    std::string _name = "";
    std::string _surname = "";
public:
    Person(const std::string& tableName = "person")
        :BaseDataType(tableName)
    {

    }

    enum PERSON
    {
        PERSON_ID,
        PERSON_NAME,
        PERSON_SURNAME,
        PERSON_SIZE
    };
    std::stringstream getFieldFromClass(int field)const override
    {
        std::stringstream buffer;
        switch (field)
        {
        case PERSON_ID:
            buffer << _id;
            return buffer;
        case PERSON_NAME:
            buffer << _name;
            return buffer;
        case PERSON_SURNAME:
            buffer << _surname;
            return buffer;
        default:
            std::cout << "ERROR Person::getFieldFromClass(int field)" << std::endl;
            break;
        }
    }
    std::string getFieldName(int field)const override
    {
        switch (field)
        {
        case PERSON_ID:
            return "person_id";
        case PERSON_NAME:
            return "first_name";
        case PERSON_SURNAME:
            return "last_name";
        default:
            std::cout << "ERROR Person::getFieldName(int field)" << std::endl;
            break;
        }
    }
    void setName(const std::string& name)
    {
        _name = name;
    }
    void setSurname(const std::string& surname)
    {
        _surname = surname;
    }
    void setId(int id)
    {
        _id = id;
    }
    std::string getName()const
    {
        return _name;
    }
    std::string getSurName()const
    {
        return _surname;
    }
    int getId()const
    {
        return _id;
    }
    std::ostream& outPut(std::ostream& out)const override
    {
        out << "Person id = " << _id << " Name is " << _name <<
            " Surname is " << _surname << std::endl;
        return out;
    }
    std::string getTableName()const override
    {
        return _tableName;
    }
    int getCountTableFields()const override
    {
        return PERSON_SIZE;
    }
   /* std::string save()const override
    {
        std::string sql;
        sql = "INSERT INTO person (first_name,last_name) VALUES ('";
        sql += this->getName() + "', '" + this->getSurName() + "')";
        return sql;
    }*/
    void setFieldsInClassFromDb(std::stringstream& buffer, int counterFieldsDefinition) override
    {
        switch (counterFieldsDefinition)
        {
        case PERSON_ID:
            buffer >> _id;
            break;
        case PERSON_NAME:
            buffer >> _name;
            break;
        case PERSON_SURNAME:
        {
            buffer >> _surname;
            break;
        }
        default:
            std::cout << "ERRROR Person::setFieldsInDb(std::stringstream& buffer, int counterFieldsDefinition)" << std::endl;
            break;
        }
    }
};