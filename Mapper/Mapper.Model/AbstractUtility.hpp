#pragma once

#include <map>
#include <vector>
#include <string>

namespace Arch
{
	using MapType = std::map<size_t, std::vector<std::string>>;
	using Strings = std::vector<std::string>;
	using FieldNames = std::initializer_list<std::string>;

	template<typename Enum>
	using wtf = std::vector<std::tuple<Enum, size_t, std::string>>;


	/*template<class T>
	class AbstractEnumUtility
	{
	public:
		virtual T getNumEnum(size_t num) const = 0;

		AbstractEnumUtility() = default;
		virtual ~AbstractEnumUtility() = default;
	};

	template<class T>
	class AbstractUtility
	{
	protected:
		wtf<T> _myWTF;
	public:
		AbstractUtility(const FieldNames& fieldNames, size_t amountFields)
		{
			size_t counter{ 0 };
			while (counter < amountFields)
			{
				_myWTF.emplace_back(std::tuple(this->getNumEnum(counter), counter, fieldNames.begin() + counter));
				++counter;
			}
		}
		virtual T getNumEnum(size_t num) const = 0;
	};*/

}