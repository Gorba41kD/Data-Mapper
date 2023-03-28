#pragma once
#include <iostream>
#include <pqxx/pqxx>

namespace Arch
{
	class Connector
	{
	private:
		std::unique_ptr<pqxx::connection> _connection;
		
		inline static std::shared_ptr<Connector> _instance{};

	private:
		Connector(std::string connectStr)
		{
			_connection = std::make_unique<pqxx::connection>(connectStr);	
		}

	public:
		static std::shared_ptr<Connector> getInstance(std::string connectionString)
		{
			if (_instance == nullptr)
			{
				_instance = std::shared_ptr<Connector>(new Connector(connectionString));
			}
			return _instance;
		}

		const std::unique_ptr<pqxx::connection>& getConnection()const noexcept
		{
			return _connection;
		}

		Connector(Connector&) = delete;
		Connector(Connector&&) = delete;

		Connector& operator=(Connector&) = delete;
		Connector& operator=(Connector&&) = delete;

		~Connector() = default;		
	};
}

