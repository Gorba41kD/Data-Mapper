#pragma once
#include"BaseDataType.h"
    class Passport :public BaseDataType
    {
    private:
        int _id = 0;
        int _serialNumber = 0;
        std::string _registration = "";

    public:
        Passport(const std::string& tableName = "passport")
            :BaseDataType(tableName)
        {

        }
        enum PASSPORT
        {
            PASSPORT_ID,
            PASSPORT_NUMBER,
            PASSPORT_REGISTRATION,
            PASSPORT_SIZE
        };

        std::string getFieldName(int field)const override
        {
            switch (field)
            {
            case PASSPORT_ID:
                return "passport_id";
            case PASSPORT_NUMBER:
                return "serial_number";
            case PASSPORT_REGISTRATION:
                return "registration";
            default:
                std::cout << "ERROR Passport::getFieldName(int field)" << std::endl;
                break;
            }
        }
        std::stringstream getFieldFromClass(int field)const override
        {
            std::stringstream buffer;
            switch (field)
            {
            case PASSPORT_ID:
                buffer << _id;
            case PASSPORT_NUMBER:
                buffer << _serialNumber;
                return buffer;
            case PASSPORT_REGISTRATION:
                buffer << _registration;
                return buffer;
            default:
                std::cout << "ERROR Passport::getFieldFromClass(int field)" << std::endl;
                break;
            }
        }
        void setId(int id)
        {
            _id = id;

        }
        void setSerialNumber(int serialNumber)
        {
            _serialNumber = serialNumber;
        }
        void setRegistration(const std::string& registration)
        {
            _registration = registration;
        }
        int getSerialNumber()const
        {
            return _serialNumber;
        }
        std::string getRegistration()const
        {
            return _registration;
        }
        int getId()const
        {
            return _id;
        }
        std::ostream& outPut(std::ostream& out)const override
        {
            out << "Passport id = " << _id << " Serial number = " << _serialNumber <<
                " Registration = " << _registration << std::endl;
            return out;
        }
        std::string getTableName()const override
        {
            return _tableName;
        }
        int getCountTableFields()const override
        {
            return PASSPORT_SIZE;
        }
        void setFieldsInDb(std::stringstream& buffer, int counterFieldsDefinition) override
        {
            switch (counterFieldsDefinition)
            {
            case PASSPORT_ID:
                buffer >> _id;
                break;
            case PASSPORT_NUMBER:
                buffer >> _serialNumber;
                break;
            case PASSPORT_REGISTRATION:
            {
                buffer >> _registration;
                break;
            }
            default:
                std::cout << "ERROR Passport::setFieldsInDb(std::stringstream& buffer, int counterFieldsDefinition)" << std::endl;
                break;
            }
        }
       /* std::string save()const override
        {
            std::string sql;
            sql = "INSERT INTO passport (serial_number,registration) VALUES (";
            sql += std::to_string(this->getSerialNumber()) + ", '" + this->getRegistration() + "')";
            return sql;
        }*/
    };
