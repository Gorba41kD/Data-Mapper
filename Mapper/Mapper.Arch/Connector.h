#pragma once
#include<pqxx/pqxx>
#include<mutex>
class Connector
{
private:
    std::mutex _tranMtx;
    pqxx::connection _connection;
    pqxx::result _response;
    pqxx::nontransaction _nonTran;
    const char* _connectionString;
public:
    Connector(const char* connectionString = "host=localhost port=5432 dbname=program user=postgres password =12081962")
        :_connectionString(connectionString), _connection(connectionString), _nonTran(_connection)
    {

    }
    pqxx::result getResponse(const std::string& sql)
    {
        std::cout << "\t\t========CONNECTOR========" << std::endl;
        std::cout << "sql code : " << sql << std::endl;
        std::lock_guard lock(_tranMtx);
        _response = _nonTran.exec(sql.c_str());
        return _response;
    }
    void sendQuery(const std::string& sql)
    {
        std::lock_guard lock(_tranMtx);
        //_nonTran.exec(sql.c_str());
    }
    void close()
    {
        _connection.close();
    }
    ~Connector()
    {
        close();
    }

};