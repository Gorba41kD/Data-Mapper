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

	class ChannelModel : public AbstractModel<ChannelFields>
	{
	private:
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
				throw std::exception("There is no field connected with this number. Check your enum");
			}
		}

	public:
		explicit ChannelModel(FieldNames names = { "id","name","owner_id" }, std::string modelName = "Channel", size_t amountFields = 3) :AbstractModel(modelName, names, amountFields)
		{
			this->init();
		}

		~ChannelModel() override = default;
	};
}
