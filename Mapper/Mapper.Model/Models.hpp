#pragma once

#include "AbstractModel.hpp"

namespace Arch
{
	/*
	* @class ChannelFields
	* @brief Includes information about channel fields. The main tool which is used to talk with model
	* @details Iteration must start from 0
	*/
	enum class ChannelFields
	{
		ID = 0,
		NAME,
		OWNER_ID 
	};

	/*
	* @class ChannelModel
	* @brief Specified instance of AbstractModel class.
	* @details Initializing of class is going by overriding internal tool-method
	*/
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
		/*
		* @method ChannelModel
		* @brief A constructor of the ChannelModel class
		* @param Initializer list consisting of column names of the table(model), like how they are in DB
		* @param Name of the table in the DB
		* @param Amount of this columns
		*/
		explicit ChannelModel(FieldNames names = { "id","name","owner_id" }, std::string modelName = "Channel", size_t amountFields = 3): AbstractModel(modelName, names, amountFields)
		{
			this->init();
		}

		~ChannelModel() override = default;
	};
}
