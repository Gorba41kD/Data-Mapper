#include "Repository.h"

void Repository::save(const Information& information)
{
    _sql = "INSERT INTO information (flight_id) VALUES (";
    _sql += std::to_string(information.getNumberOfAirLine()) + ")";
    _nonTran.exec(_sql.c_str());
}
void Repository::save(const Passport& passport)
{
    _sql = "INSERT INTO passport (serial_number,registration) VALUES (";
    _sql += std::to_string(passport.getSerialNumber()) + ", '" + passport.getRegistration() + "')";
    _nonTran.exec(_sql.c_str());
}
void Repository::save(const Person& person)
{
    _sql = "INSERT INTO person (first_name,last_name) VALUES ('";
    _sql += person.getName() + "', '" + person.getSurName() + "')";
    _nonTran.exec(_sql.c_str());
}
void Repository::print()
{
    for (auto it = _containerAirLine.begin(); it != _containerAirLine.end(); ++it)
    {
        std::cout << it->second;
    }
}
void Repository::printInformation()
{
    _response = _nonTran.exec("SELECT * FROM history");
    int j = 1;
    for (size_t i = 0; i < _response.size(); i++)
    {
        std::cout << j++ << ": " << _response[i][HISTORY_NAME] << " " << _response[i][HISTORY_SURNAME] << " Flight id: " << _response[i][HISTORY_FLIGHT_ID] << " AirLine: " << _response[i][HISTORY_AIRLINE]
            << " Departure airport: " << _response[i][HISTORY_DEPARTURE_AIRPORT] << " Arrival airport: " << _response[i][HISTORY_ARRIVAL_AIRPORT]
            << " Price: " << _response[i][HISTORY_PRICE] << std::endl;
    }
}
std::map<int, AirLine> Repository::get()const
{
    return _containerAirLine;
}
std::map<int, AirLine> Repository::read()
{
    _response = _nonTran.exec("SELECT * FROM flight");
    AirLine airLine;
    for (pqxx::result::const_iterator it = _response.begin(); it != _response.end(); ++it)
    {
        airLine.setId(it[AIRLINE_ID].as<int>());
        airLine.setAirLine(it[AIRLINE].as<std::string>());
        airLine.setDepAir(it[AIRLINE_DEPARTURE_AIRPORT].as<std::string>());
        airLine.setArrAir(it[AIRLINE_ARRIVAL_AIRPORT].as<std::string>());
        airLine.setDepDate(it[AIRLINE_DEPARTURE_DATE].as<std::string>());
        airLine.setDepTime(it[AIRLINE_DEPARTURE_TIME].as<std::string>());
        airLine.setPrice(it[AIRLINE_PRICE].as<double>());
        _containerAirLine.emplace(airLine.getId(), airLine);
    }
    return _containerAirLine;
}
