#pragma once

#include <map>
#include <vector>
#include <string>
#include <regex>
#include <map>
#include "AbstractModel.hpp"

namespace Arch
{
	using MapType = std::map<size_t, std::vector<std::string>>;
	using Strings = std::vector<std::string>;
	using FieldNames = std::initializer_list<std::string>;

	template<typename TKey>
	class Comparator
	{
	public:
		bool operator()(const TKey& first, const TKey& second) const noexcept
		{
			return static_cast<size_t>(first) < static_cast<size_t>(second);
		}
	};

	template<typename TKey, typename TData = std::string, typename Comp = Comparator<TKey>>
	class Map : public std::map<TKey, TData, Comp>
	{
	};

	template<typename Enum>
	using FieldData = std::vector<std::tuple<Enum, size_t, std::string>>;
	
}
