#pragma once

#include "AbstractModel.hpp"

namespace Arch
{
	class ChannelModel : public AbstractModel
	{
	public:
		enum ChannelFields
		{
			ID = 0,
			NAME = 1,
			OWNER_ID = 2
		};

		void fillMap(const pqxx::result::const_iterator& info) override
		{
			_data[ID].emplace_back(info[ID].as <std::string>());
			_data[NAME].emplace_back(info[NAME].as<std::string>());
			_data[OWNER_ID].emplace_back(info[OWNER_ID].as<std::string>());
		}

		explicit ChannelModel(std::string modelName = "Channel", size_t amountFields = 3) :AbstractModel(modelName, amountFields)
		{
			_data.emplace(ID, Strings());
			_data.emplace(NAME, Strings());
			_data.emplace(OWNER_ID, Strings());
		}

		~ChannelModel() override = default;
	};
}
