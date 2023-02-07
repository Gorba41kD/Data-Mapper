#pragma once
#include <map>
#include <vector>
#include <string>
#include <string_view>
#include <pqxx/pqxx>

namespace Arch
{
	using MapType = std::map<size_t, std::vector<std::string>>;
	using Strings = std::vector<std::string>;
	using AdvancedMap = std::tuple<int>;

	class AbstractModel
	{
		std::string _modelName;
		size_t _amountOfFields;

	public:
		explicit AbstractModel(const std::string& modelName, size_t amountFields) : _modelName(modelName), _amountOfFields(amountFields) {}

		MapType& getMap()noexcept { return _data; }
		const std::string_view getModelName()const noexcept { return _modelName; }

		virtual const std::string_view getFieldName()const noexcept = 0;
		virtual void fillMap(const pqxx::result::const_iterator&) = 0;

		virtual ~AbstractModel() = default;

	protected:
		MapType _data;
	};
}
