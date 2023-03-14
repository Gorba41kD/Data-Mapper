#pragma once
#include <pqxx/pqxx>
#include "AbstractUtility.hpp"

namespace Arch
{
	// обернуть в синглтон чтобы я мог настроить абстрактную модель
	template <typename T>
	class AbstractModel
	{
	private:
		std::string _modelName;
		size_t _amountOfFields;

	protected:
		MapType _data;
		wtf<T> _myWTF;

	public:
		explicit AbstractModel(const std::string& modelName, FieldNames names, size_t amountFields) :_modelName(modelName), _amountOfFields(amountFields) /*,AbstractUtility<T>(names, amountFields)*/
		{
			size_t counter{ 0 };
			while (counter < amountFields)
			{
				_myWTF.emplace_back(std::make_tuple<T,size_t,std::string>(this->getNumEnum(counter), std::move(counter), (names.begin()+counter)->c_str()));
				++counter;
			}
		}

		MapType& getMap()noexcept { return _data; }
		const std::string getModelName()const noexcept { return _modelName; }

		virtual const size_t getNumFromEnum()const noexcept = 0;
		virtual const std::string getFieldName(size_t)const noexcept = 0;
		virtual void fillMap(const pqxx::result::const_iterator&) = 0;
		virtual T getNumEnum(size_t num) const = 0;

		virtual ~AbstractModel() = default;
	};
}
