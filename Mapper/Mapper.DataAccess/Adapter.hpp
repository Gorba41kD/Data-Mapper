#pragma once
#include <string>
#include <pqxx/pqxx>
#include "AbstractModel.hpp"

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

		void read(AbstractModel& model, const std::string& groupBy = "")
		{
			std::string _sql;

			_sql = "SELECT * FROM ";
			_sql += '"';
			_sql += model.getModelName();
			_sql += '"';
			_sql += groupBy;

			auto response = _nonTran.exec(_sql.c_str());

			for (auto&& iter = response.begin(); iter != response.end(); ++iter)
			{
				model.fillMap(iter);
			}
		}
	};
}


