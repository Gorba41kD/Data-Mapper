#pragma once

#include "AbstractModel.hpp"

namespace Arch
{
	enum class ChannelFields
	{
		ID = 0,
		NAME = 1,
		OWNER_ID = 2
	};
		
	class ChannelModel: public AbstractModel<ChannelFields>
	{
	public:
		ChannelFields getNumEnum(size_t num)const override
		{
			switch (num)
			{
			case 0:
				return ChannelFields::ID;
			case 1:
				return ChannelFields::NAME;
			case 2:
				return ChannelFields::OWNER_ID;
			default:
				std::exception("There is no field connected with this number. Check EnumUtility");
			}
		}

		void fillMap(const pqxx::result::const_iterator& info) override
		{
			//_data[ID].emplace_back(info[ID].as <std::string>());
			//_data[NAME].emplace_back(info[NAME].as<std::string>());
			//_data[OWNER_ID].emplace_back(info[OWNER_ID].as<std::string>());
		}

		explicit ChannelModel(FieldNames names = { "id","name","owner_ID" }, std::string modelName = "Channel", size_t amountFields = 3) :AbstractModel(modelName,names, amountFields)
		{
			this->init();
		}

		const size_t enumToNum(ChannelFields anyEnum)const noexcept override
		{
			return std::get<1>(*std::find_if(_myWTF.begin(), _myWTF.end(), [anyEnum](std::tuple<ChannelFields, size_t, std::string> tpl) {if (std::get<0>(tpl) == anyEnum) return true; }));
		}

		const std::string fieldName(ChannelFields anyEnum)const noexcept override
		{
			return std::get<2>(*std::find_if(_myWTF.begin(), _myWTF.end(), [anyEnum](std::tuple<ChannelFields, size_t, std::string> tpl) {if (std::get<0>(tpl) == anyEnum) return true; }));
		}

		~ChannelModel() override = default;
	};
}
