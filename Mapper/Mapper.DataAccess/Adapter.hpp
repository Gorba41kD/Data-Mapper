#pragma once
#include <string>
#include <pqxx/pqxx>
#include "AbstractModel.hpp"
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

		template<typename T>
		void read(AbstractModel<T>& model, std::initializer_list<T> listFields, std::string whereCondition="")
		{
			{
				std::string sql{"SELECT "};
				std::string fields{ "*" };
				
				if (listFields.size())
				{
					fields.clear();

					std::for_each(listFields.begin(), listFields.end(), [&fields, &model](T someEnum)
						{
							fields += model.fieldName(someEnum);
							fields += ",";
						}
					);
					fields.erase(fields.end() - 1);
				}
				
				sql += fields;
				sql += ' ';

				sql += "FROM ";
				sql += '"';
				sql += model.getModelName();
				sql += '"';

				auto response = _nonTran.exec(sql.c_str());

				model.fillMap(response, listFields);

				for (auto&& iter = response.begin(); iter != response.end(); ++iter)
				{
					model.fillMap(iter);
				}
			}
		}		
	};
}


