#pragma once
#include<pqxx/pqxx>
#include"IRepository.h"
template<typename T>
class Repository :public IRepository<T>
{
private:
    enum Convert
    {
        CONVERT_TO_INT,
        CONVERT_TO_STRING,
        CONVERT_TO_DOUBLE
    };
    pqxx::connection _connection;
    pqxx::result _response;
    pqxx::nontransaction _nonTran;
    std::string _sql;
    Convert checkFieldInDb(const std::string& fieldDb)
    {
        int counter = 0;
        int fieldDbToInt = 0;
        for (int i = 0; i < fieldDb.size(); ++i)
        {
            if (isdigit(fieldDb[i]))
            {
                counter++;
            }
            else
            {
                break;
            }
        }
        if (counter == fieldDb.size())
        {
            return CONVERT_TO_INT;
        }
        else if (fieldDb.find(':') != std::string::npos || fieldDb.find('-') != std::string::npos)
        {
            return CONVERT_TO_STRING;
        }
        else if (fieldDb.find('.') != std::string::npos || fieldDb.find(',') != std::string::npos)
        {
            return CONVERT_TO_DOUBLE;
        }
        else
        {
            return CONVERT_TO_STRING;
        }
    }
public:
    Repository(const char* connectionString = "host=localhost port=5432 dbname=program user=postgres password =12081962")
        : _connection(connectionString), _nonTran(_connection)
    {
    }
    void readModel(std::unique_ptr<T>& model, const std::vector<int>& fields, int id = 1)override
    {
        std::string ID = std::to_string(id);
        _sql = "SELECT ";
        int firstField = 0;
        if (fields[firstField] == model->getCountTableFields())
        {
            for (int field = 0; field < model->getCountTableFields(); ++field)
            {
                _sql += model->getFieldName(field);
                if (field != model->getCountTableFields() - 1)
                {
                    _sql += ", ";
                }
            }
            _sql += " FROM ";
            _sql += model->getTableName();
            _sql += " WHERE ";
            _sql += model->getTableName();
            _sql += "_id = ";
            _sql += ID;
            std::cout << "sql code: " << _sql << std::endl;
            _response = _nonTran.exec(_sql.c_str());
            pqxx::result::const_iterator it = _response.begin();
            int setField = 0;
            for (; setField < fields[firstField]; ++setField)
            {
                auto value = it[setField].as<std::string>();
                std::stringstream buffer;
                switch (checkFieldInDb(value))
                {
                case CONVERT_TO_INT:
                    buffer << it[setField].as<int>();
                    break;
                case CONVERT_TO_DOUBLE:
                    buffer << it[setField].as<double>();
                    break;
                case CONVERT_TO_STRING:
                    buffer << it[setField].as<std::string>();
                    break;
                default:
                    std::cout << "LOOK AT Repository::readModel(std::unique_ptr<BaseDataType>& model, const std::vector<int>& fields, int id = 1)override" << std::endl;
                    break;
                }
                model->setFieldsInDb(buffer, setField);
            }
        }
        else
        {
            for (const auto field : fields)
            {
                _sql += model->getFieldName(field);
                if (field != *(fields.end() - 1))
                {
                    _sql += ", ";
                }
            }
            _sql += " FROM ";
            _sql += model->getTableName();
            _sql += " WHERE ";
            _sql += model->getTableName();
            _sql += "_id = ";
            _sql += ID;
            std::cout << "sql code: " << _sql << std::endl;
            _response = _nonTran.exec(_sql.c_str());
            pqxx::result::const_iterator it = _response.begin();
            for (int setField = 0; setField < fields.size(); ++setField)
            {
                auto value = it[setField].as<std::string>();
                std::stringstream buffer;
                switch (checkFieldInDb(value))
                {
                case CONVERT_TO_INT:
                    buffer << it[setField].as<int>();
                    break;
                case CONVERT_TO_DOUBLE:
                    buffer << it[setField].as<double>();
                    break;
                case CONVERT_TO_STRING:
                    buffer << it[setField].as<std::string>();
                    break;
                default:
                    std::cout << "LOOK AT Repository::readModel(std::unique_ptr<BaseDataType>& model, const std::vector<int>& fields, int id = 1)override" << std::endl;
                    break;
                }
                model->setFieldsInDb(buffer, fields[setField]);
            }
        }
    }
    std::map<int, std::shared_ptr<T>> readCollections(const std::vector<int>& fields)override
    {
        std::map<int, std::shared_ptr<T>> container;
        std::unique_ptr<T> temp = std::make_unique<T>();
        _sql = "SELECT ";
        int firstField = 0;
        if (fields[firstField] == temp->getCountTableFields())
        {
            auto last = temp->getCountTableFields() - 1;
            for (int field = 0; field < temp->getCountTableFields(); ++field)
            {
                _sql += temp->getFieldName(field);
                if (field != last)
                {
                    _sql += ", ";
                }
            }
            _sql += " FROM ";
            _sql += temp->getTableName();
            std::cout << "sql code: " << _sql << std::endl;
            _response = _nonTran.exec(_sql.c_str());
            for (pqxx::result::const_iterator it = _response.begin(); it != _response.end(); ++it)
            {
                auto model = std::make_unique<T>();
                int setField = 0;
                for (; setField < fields[firstField]; ++setField)
                {
                    auto value = it[setField].as<std::string>();
                    std::stringstream buffer;
                    switch (checkFieldInDb(value))
                    {
                    case CONVERT_TO_INT:
                        buffer << it[setField].as<int>();
                        break;
                    case CONVERT_TO_DOUBLE:
                        buffer << it[setField].as<double>();
                        break;
                    case CONVERT_TO_STRING:
                        buffer << it[setField].as<std::string>();
                        break;
                    default:
                        std::cout << "LOOK AT Repository::readCollections(const std::vector<int>& fields)override" << std::endl;
                        break;
                    }
                    model->setFieldsInDb(buffer, setField);
                }
                container.emplace(model->getId(), std::move(model));
            }
        }
        else
        {
            auto lastField = *(fields.end() - 1);
            for (const auto field : fields)
            {
                _sql += temp->getFieldName(field);
                if (field != lastField)
                {
                    _sql += ", ";
                }
            }
            _sql += " FROM ";
            _sql += temp->getTableName();
            std::cout << "sql code: " << _sql << std::endl;
            _response = _nonTran.exec(_sql.c_str());
            for (pqxx::result::const_iterator it = _response.begin(); it != _response.end(); ++it)
            {
                auto model = std::make_unique<T>();
                for (int setField = 0; setField < fields.size(); ++setField)
                {
                    auto value = it[setField].as<std::string>();
                    std::stringstream buffer;
                    switch (checkFieldInDb(value))
                    {
                    case CONVERT_TO_INT:
                        buffer << it[setField].as<int>();
                        break;
                    case CONVERT_TO_DOUBLE:
                        buffer << it[setField].as<double>();
                        break;
                    case CONVERT_TO_STRING:
                        buffer << it[setField].as<std::string>();
                        break;
                    default:
                        std::cout << "LOOK AT Repository::readCollections(const std::vector<int>& fields)override" << std::endl;
                        break;
                    }
                    model->setFieldsInDb(buffer, fields[setField]);
                }
                container.emplace(model->getId(), std::move(model));
            }

        }
        return container;
    }
    //void save(const std::unique_ptr<T>& model)override
    //{
    //    _sql = model->save();
    //    std::cout << "sql = " << _sql << std::endl;
    //    //_nonTran.exec(_sql.c_str());
    //}

    void save(const std::unique_ptr<T>& model) override
    {
        _sql = "INSERT INTO ";
        _sql += model->getTableName();
        _sql += " (";
        for (size_t field = 1; field < model->getCountTableFields(); ++field)
        {
            _sql += model->getFieldName(field);
            if (field != model->getCountTableFields() - 1)
            {
                _sql += ",";
            }
        }
        _sql += ") VALUES (";
        for (size_t field = 1; field < model->getCountTableFields(); ++field)
        {
            std::string value;
            std::stringstream buffer;
            buffer = model->getFieldFromClass(field);
            buffer >> value;
            switch (checkFieldInDb(value))
            {
            case CONVERT_TO_INT:
            case CONVERT_TO_DOUBLE:
                _sql += value;
                break;
            case CONVERT_TO_STRING:
                _sql += "'";
                _sql += value;
                _sql += "'";
                break;
            }
            if (field != model->getCountTableFields() - 1)
            {
                _sql += ", ";
            }
        }
        _sql += ")";
        std::cout << "sql code: " << _sql << std::endl;
        //_nonTran.exec(_sql.c_str());
    }
    ~Repository()
    {
        _connection.close();
    }

    /*std::map<int, std::shared_ptr<T>> readSpecificCollectionsSecondVariant(const std::vector<int>& fields)
    {
        std::map<int, std::shared_ptr<T>> container;
        T model;
        _sql = "SELECT ";
        int firstField = 0;
        int size = 0;
        if (fields[firstField] == model.getCountTableFields())
        {
            for (int field = 0; field < model.getCountTableFields(); ++field)
            {
                _sql += model.getTableName(field);
                if (field != model.getCountTableFields() - 1)
                {
                    _sql += ", ";
                }
            }
            size = model.getCountTableFields();
        }
        else
        {
            for (const auto field : fields)
            {
                _sql += model.getTableName(field);
                if (field != *(fields.end() - 1))
                {
                    _sql += ", ";
                }
            }
            size = fields.size();
        }
        _sql += " FROM ";
        _sql += model.getTableName();
        std::cout << "sql code: " << _sql << std::endl;
        _response = _nonTran.exec(_sql.c_str());
        for (pqxx::result::const_iterator it = _response.begin(); it != _response.end(); ++it)
        {
            auto person = std::make_unique<T>();
            int setField = 0;
            for (; setField < size; ++setField)
            {
                auto value = it[setField].as<std::string>();
                std::stringstream buffer;
                switch (checkFieldInDb(value))
                {
                case CONVERT_TO_INT:
                    buffer << it[setField].as<int>();
                    break;
                case CONVERT_TO_DOUBLE:
                    buffer << it[setField].as<double>();
                    break;
                case CONVERT_TO_STRING:
                    buffer << it[setField].as<std::string>();
                    break;
                default:
                    std::cout << "LOOK AT Repository::readContainer(AbstractModelUtility& model)" << std::endl;
                    break;
                }
                person->setFieldsInDb(buffer, setField);
            }
            container.emplace(person->getId(), std::move(person));
        }
        return container;
    }
    void readModelSecondVariant(std::unique_ptr<BaseDataType>& model, const std::vector<int>& fields, int id = 1)
    {
        std::string ID = std::to_string(id);
        _sql = "SELECT ";
        int firstField = 0;
        int size = 0;
        if (fields[firstField] == model->getCountTableFields())
        {
            for (int field = 0; field < model->getCountTableFields(); ++field)
            {
                _sql += model->getTableName(field);
                if (field != model->getCountTableFields() - 1)
                {
                    _sql += ", ";
                }
            }
            size = model->getCountTableFields();
        }
        else
        {
            for (const auto field : fields)
            {
                _sql += model->getTableName(field);
                if (field != *(fields.end() - 1))
                {
                    _sql += ", ";
                }
            }
            size = fields.size();
        }
        _sql += " FROM ";
        _sql += model->getTableName();
        _sql += " WHERE ";
        _sql += model->getTableName();
        _sql += "_id = ";
        _sql += ID;
        std::cout << "sql code: " << _sql << std::endl;
        _response = _nonTran.exec(_sql.c_str());
        pqxx::result::const_iterator it = _response.begin();
        int setField = 0;
        for (; setField < size; ++setField)
        {
            auto value = it[setField].as<std::string>();
            std::stringstream buffer;
            switch (checkFieldInDb(value))
            {
            case CONVERT_TO_INT:
                buffer << it[setField].as<int>();
                break;
            case CONVERT_TO_DOUBLE:
                buffer << it[setField].as<double>();
                break;
            case CONVERT_TO_STRING:
                buffer << it[setField].as<std::string>();
                break;
            default:
                std::cout << "LOOK AT Repository::readContainer(AbstractModelUtility& model)" << std::endl;
                break;
            }
            model->setFieldsInDb(buffer, setField);
        }
    }*/
};