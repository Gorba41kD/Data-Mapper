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
	
}