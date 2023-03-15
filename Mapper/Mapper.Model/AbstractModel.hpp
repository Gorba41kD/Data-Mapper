#pragma once
#include <pqxx/pqxx>
#include "AbstractUtility.hpp"

namespace Arch
{
	template <typename T>
	class AbstractModel
	{
	private:
		std::string _modelName;
		size_t _amountOfFields;
		std::vector<std::string> _fieldNames;

	protected:
		MapType _data;
		wtf<T> _myWTF;

	public:
		explicit AbstractModel(const std::string& modelName, FieldNames names, size_t amountFields) :_modelName(modelName), _amountOfFields(amountFields), _fieldNames(names) {}

		//MapType& getMap()noexcept { return _data; }
		const std::string getModelName()const noexcept { return _modelName; }

		virtual const size_t enumToNum(T anyEnum)const noexcept
		{
			return std::get<1>(*std::find_if(_myWTF.begin(), _myWTF.end(), [anyEnum](std::tuple<T, size_t, std::string> tpl) {if (std::get<0>(tpl) == anyEnum) return true; else return false; }));
		}
		virtual const std::string fieldName(T anyEnum)const noexcept
		{
			return std::get<2>(*std::find_if(_myWTF.begin(), _myWTF.end(), [anyEnum](std::tuple<T, size_t, std::string> tpl) {if (std::get<0>(tpl) == anyEnum) return true; else return false; }));
		}

		virtual void fillMap(const pqxx::result& response, std::initializer_list<T> fields)
		{
			std::for_each(response.begin(), response.end(), [fields,&_data]() 
				{
					
				}
			);
		}

		virtual ~AbstractModel() = default;

	protected:
		void init()
		{
			size_t counter{ 0 };
			while (counter < _amountOfFields)
			{
				_myWTF.emplace_back(std::make_tuple<T, size_t, std::string>(this->getNumEnum(counter), std::move(counter), (_fieldNames.begin() + counter)->c_str()));
				++counter;
			}
			_fieldNames.clear();
		}

	private:
		virtual T getNumEnum(size_t num) const = 0;
	};
}
