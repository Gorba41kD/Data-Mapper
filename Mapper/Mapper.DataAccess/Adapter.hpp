#pragma once
#include <string>
#include <pqxx/pqxx>
#include "Models.hpp"

namespace Arch
{
	class Adapter
	{
	private:
		pqxx::connection _connection;
		pqxx::nontransaction _nonTran;

	public:
		// host=localhost port=5432 dbname=program user=postgres password =1221909128 <- connectString
		explicit Adapter(const std::string& connectString = "host=localhost port=5432 dbname=program user=postgres password=1221909128") :_connection(connectString), _nonTran(_connection) {}

		//void read(AbstractModel& model, const std::string& groupBy = "");
		
	};
}


