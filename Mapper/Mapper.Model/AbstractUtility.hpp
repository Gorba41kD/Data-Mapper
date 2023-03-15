#pragma once

#include <map>
#include <vector>
#include <string>
#include <regex>
#include "AbstractModel.hpp"

namespace Arch
{
	using MapType = std::map<size_t, std::vector<std::string>>;
	using Strings = std::vector<std::string>;
	using FieldNames = std::initializer_list<std::string>;

	template<typename Enum>
	using FieldData = std::vector<std::tuple<Enum, size_t, std::string>>;
	
}
