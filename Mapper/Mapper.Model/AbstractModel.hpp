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
		explicit AbstractModel(const std::string& modelName, FieldNames names, size_t amountFields) :_modelName(modelName), _amountOfFields(amountFields), _fieldNames(names){}

		MapType& getMap()noexcept { return _data; }
		const std::string getModelName()const noexcept { return _modelName; }

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

		virtual const size_t enumToNum(T anyEnum)const noexcept = 0;
		virtual const std::string fieldName(T)const noexcept = 0;
		virtual void fillMap(const pqxx::result::const_iterator&) = 0;
			
		virtual ~AbstractModel() = default;

	private:
		virtual T getNumEnum(size_t num) const = 0;
	};
}
