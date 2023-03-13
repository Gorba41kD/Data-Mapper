#include "Adapter.hpp"

namespace Arch 
{
	void Adapter::read(AbstractModel& model, const std::string& groupBy = "")
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
}