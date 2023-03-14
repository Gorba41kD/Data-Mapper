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

	template<class T = ChannelFields>
	class ChannelModel : public AbstractModel<T>
	{
	public:
		virtual T AbstractModel<T>::getNumEnum(size_t num)const
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
			
		}

		const size_t getNumFromEnum()const noexcept override
		{
			return 1;
		}

		const std::string getFieldName(size_t)const noexcept override
		{
			return "kek";
		}


		~ChannelModel() override = default;
	};
}
