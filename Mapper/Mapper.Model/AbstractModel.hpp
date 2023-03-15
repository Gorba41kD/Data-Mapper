#pragma once
#include <pqxx/pqxx>
#include "AbstractUtility.hpp"

namespace Arch
{
	/*
	* @class AbstractModel
	* @brief An abstract class which includes interface which will be initialized later by user
	* @details Contains information about table, data of the table and so on
	* @todo Divide the class into new ones because of S(OLID)
	*/
	template <typename T>
	class AbstractModel
	{
	private:
		std::string _modelName;
		size_t _amountOfFields;
		std::vector<std::string> _fieldNames;

	protected:
		MapType _data;
		FieldData<T> _fieldData;

	public:
		explicit AbstractModel(const std::string& modelName, FieldNames names, size_t amountFields) :_modelName(modelName), _amountOfFields(amountFields), _fieldNames(names) {}

		constexpr std::string getModelName()const noexcept { return _modelName; }
		const size_t enumToNum(T anyEnum)const noexcept
		{
			return std::get<1>(*std::find_if(_fieldData.begin(), _fieldData.end(), [anyEnum](std::tuple<T, size_t, std::string> tpl) {if (std::get<0>(tpl) == anyEnum) return true; else return false; }));
		}
		const std::string fieldName(T anyEnum)const noexcept
		{
			return std::get<2>(*std::find_if(_fieldData.begin(), _fieldData.end(), [anyEnum](std::tuple<T, size_t, std::string> tpl) {if (std::get<0>(tpl) == anyEnum) return true; else return false; }));
		}

		const std::vector<T>& getAllFields()
		{	
			std::vector<T> temp;
			for (size_t i{ 0 }; i < _fieldData.size(); ++i)
				temp.emplace_back(std::get<0>(_fieldData[i]));
			
			return temp;
		}

		void fillMap(const pqxx::result& response, const std::vector<T>& fields)
		{
			for (auto respIter = response.begin(); respIter != response.end(); ++respIter)
			{
				for (auto fieldIter = fields.begin(); fieldIter != fields.end(); ++fieldIter)
				{
					_data[this->enumToNum(*fieldIter)].emplace_back(respIter[this->enumToNum(*fieldIter)].as<std::string>());
				}
			}
		}

		std::vector<std::string>& operator[](T anyEnum)
		{
			return _data[enumToNum(anyEnum)];
		}

		virtual ~AbstractModel() = default;

	protected:
		void init()
		{
			size_t counter{ 0 };
			while (counter < _amountOfFields)
			{
				_fieldData.emplace_back(std::make_tuple<T, size_t, std::string>(this->getNumEnum(counter), std::move(counter), (_fieldNames.begin() + counter)->c_str()));
				_data.insert(std::pair<size_t, std::vector<std::string>>(counter, std::vector<std::string>()));
				++counter;
			}
			_fieldNames.clear();
		}

	private:
		/*
		* @method getNumEnum
		* @param size_t num -> used to find all objects from specific enum class
		* @returns Object of specific enum class
		*/
		virtual T getNumEnum(size_t num) const = 0;
	};
}
