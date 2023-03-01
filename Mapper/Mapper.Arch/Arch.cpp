#include"iostream"
#include<pqxx/pqxx>
#include"string"
#include"map"
#include"memory"
namespace ORM
{
    class Person;
    class Passport;
    class AbstractModelUtility
    {
    public:
        AbstractModelUtility(std::string tableName)
            :_tableName(tableName)
        {

        }
        virtual ~AbstractModelUtility() {};
        virtual std::ostream& outPut(std::ostream& out) const = 0;
        virtual std::string getTableName()const = 0;
        virtual void setFieldsInDb(std::stringstream& buffer, int counterFieldsDefinition) = 0;
        virtual int getCountTableFields()const = 0;
    protected:
        std::string _tableName;
    };

    class Passport :public AbstractModelUtility
    {
    private:
        int _id;
        int _serialNumber;
        std::string _registration;

    public:
        Passport(const std::string& tableName = "passport")
            :AbstractModelUtility(tableName)
        {

        }
        enum PASSPORT
        {
            PASSPORT_ID,
            PASSPORT_NUMBER,
            PASSPORT_REGISTRATION,
            PASSPORT_SIZE
        };
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
                std::cout << "ERRROR Passport::setFieldsInDb(std::stringstream& buffer, int counterFieldsDefinition)" << std::endl;
                break;
            }
        }
    };
    class Person :public AbstractModelUtility
    {
    private:
        int _id;
        std::string _name;
        std::string _surname;
    public:
        Person(const std::string& tableName = "person")
            :AbstractModelUtility(tableName)
        {

        }

        enum PERSON
        {
            PERSON_ID,
            PERSON_NAME,
            PERSON_SURNAME,
            PERSON_SIZE
        };
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
        void setFieldsInDb(std::stringstream& buffer, int counterFieldsDefinition) override
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
    std::ostream& operator <<(std::ostream& out, const AbstractModelUtility* parent)
    {
        return parent->outPut(out);
    }
    class Irepository
    {
    public:
        virtual void read(std::unique_ptr<AbstractModelUtility>& model, int id = 1) = 0;
        virtual std::map<int, std::shared_ptr<AbstractModelUtility>> readContainer(AbstractModelUtility& models) = 0;
        virtual void print() = 0;
        virtual ~Irepository() {}
    };
    class Repository :public Irepository
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
        std::map<int, std::shared_ptr<AbstractModelUtility>> _container;
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
        void print() override
        {
            for (auto it = _container.begin(); it != _container.end(); ++it)
            {
                std::cout << it->second;
            }
        }
        std::map<int, std::shared_ptr<AbstractModelUtility>> readContainer(AbstractModelUtility& model) override
        {
            if (!_container.empty())
            {
                _container.clear();
            }
            _sql = "SELECT * FROM ";
            _sql += model.getTableName();
            std::cout << "sql code: " << _sql << std::endl;
            _response = _nonTran.exec(_sql.c_str());
            if (model.getTableName() == "person")
            {
                for (pqxx::result::const_iterator it = _response.begin(); it != _response.end(); ++it)
                {
                    auto person = std::make_unique<Person>();
                    auto localModel = 5;
                    int setField = 0;
                    for (; setField < model.getCountTableFields(); ++setField)
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
                    _container.emplace(person->getId(), std::move(person));
                }
                return _container;
            }
            else if (model.getTableName() == "passport")
            {
                for (pqxx::result::const_iterator it = _response.begin(); it != _response.end(); ++it)
                {
                    auto passport = std::make_unique<Passport>();
                    int setField = 0;
                    for (; setField < model.getCountTableFields(); ++setField)
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
                        passport->setFieldsInDb(buffer, setField);
                    }
                    _container.emplace(passport->getId(), std::move(passport));
                }
                return _container;
            }
            else
            {
                std::cout << "LOOK AT Repository::readContainer(AbstractModelUtility& model)" << std::endl;
            }
        }
        void read(std::unique_ptr<AbstractModelUtility>& model, int id = 1) override
        {
            std::string ID = std::to_string(id);
            _sql = "SELECT * FROM ";
            _sql += model->getTableName();
            _sql += " WHERE ";
            _sql += model->getTableName();
            _sql += "_id = ";
            _sql += ID;
            std::cout << _sql << std::endl;
            _response = _nonTran.exec(_sql.c_str());
            for (pqxx::result::const_iterator it = _response.begin(); it != _response.end(); ++it)
            {
                int setField = 0;
                for (; setField < model->getCountTableFields(); ++setField)
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
            }
        }
        Repository(const char* connectionString = "host=localhost port=5432 dbname=program user=postgres password =12081962")
            : _connection(connectionString), _nonTran(_connection)
        {
        }
        ~Repository()
        {
            _connection.close();
        }
    };
}
int main()
{
    try
    {
        std::unique_ptr<ORM::Irepository> repository = std::make_unique<ORM::Repository>();
        ORM::Person person;
        ORM::Passport passport;

        std::unique_ptr<ORM::AbstractModelUtility> modelPerson = std::make_unique<ORM::Person>(person);
        repository->read(modelPerson);
        std::cout << modelPerson;

        std::unique_ptr<ORM::AbstractModelUtility> modelPassport = std::make_unique<ORM::Passport>(passport);
        repository->read(modelPassport);
        std::cout << modelPassport;

        repository->readContainer(person);
        repository->print();

        repository->readContainer(passport);
        repository->print();

        /* std::cout << checkFieldInDb("Dima") << std::endl;
         std::cout << checkFieldInDb("111") << std::endl;
         std::cout << checkFieldInDb("2022-12-12") << std::endl;
         std::cout << checkFieldInDb("14:30:00") << std::endl;
         std::cout << checkFieldInDb("5,6") << std::endl;
         std::cout << checkFieldInDb("4.4") << std::endl;*/
    }
    catch (std::exception& exc)
    {
        std::cout << exc.what();
    }
    return 0;
}
