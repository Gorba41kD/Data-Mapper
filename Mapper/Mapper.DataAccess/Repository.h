#pragma once
#include"Irepository.h"
#include <pqxx/pqxx>
#include"../Mapper.Utility/enum_AirLine.h"
#include"../Mapper.Utility/enum_History.h"
#include"../Mapper.Model/Information.h"

class Repository :public Irepository
{
private:
    pqxx::connection _connection;
    pqxx::result _response;
    pqxx::nontransaction _nonTran;
    std::string _sql;
    std::map<int, AirLine> _containerAirLine;

public:
    void save(const Information& information)override;
    void save(const Passport& passport) override;
    void save(const Person& person)override;
    void print() override;
    void printInformation() override;
    std::map<int, AirLine> get()const override;
    std::map<int, AirLine> read()override;

    Repository(const char* connectionString = "host=localhost port=5432 dbname=program user=postgres password =12081962")
        : _connection(connectionString), _nonTran(_connection)
    {

    }
    ~Repository()
    {
        _connection.close();
    }
};

