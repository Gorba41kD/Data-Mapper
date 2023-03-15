#pragma once
#include <string>
#include <pqxx/pqxx>
#include <regex>
#include "AbstractModel.hpp"
#include "Models.hpp"

namespace Arch
{
	/*
	* @class Adapter
	* @brief Class which provides ability to 'talk' with database(only postgres rn) easily by models
	* @details 
	*/
	class Adapter
	{
	private:
		pqxx::connection _connection;
		pqxx::nontransaction _nonTran;

	public:		
		/*
		* @param Connection string to your database
		*/
		explicit Adapter(const std::string& connectString = "host=localhost port=5432 dbname=program user=postgres password=1221909128") :_connection(connectString), _nonTran(_connection) {}

		/*
		* @method read
		* @brief Reads the data from database using some specification
		* @param Model, which will be filled by data
		* @param List of columns, that user want to have(may not be used)
		* @param Where condition(may not be used)
		*/
		template<typename T>
		void read(AbstractModel<T>& model, const std::initializer_list<T>& listFields = {}, const std::string& whereCondition = "")
		{
			{
				std::string sql{"SELECT "};
				std::string fields{ "*" };
				std::vector<T> temporaryFields(listFields);
				
				if (temporaryFields.size()) /// possibly it's going to transform into the method
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
				else
				{
					temporaryFields = model.getAllFields();
				}
				
				sql += fields;
				sql += ' ';

				sql += "FROM ";
				sql += '"';
				sql += model.getModelName();
				sql += '"';


				/*if (whereCondition.size())
				{
					std::regex rgxStart("^[\(]");
					std::regex rgxEnd("[\)]$");
					std::regex rgxPunc("(.+)[,](.+)");
				}*/

				// ^[\(]((?:id)((((>)|(<)|(=)|(>=)|(<=))([0-9]*+))|(([=]|[>]|[<])(\')((.+)|())(\'))))[\)]$
				

				auto response = _nonTran.exec(sql.c_str());

				model.fillMap(response, temporaryFields);
			}
		}		
	};
}
