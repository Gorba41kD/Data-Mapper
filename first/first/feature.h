#pragma once
#include<vector>
#include"AirLine.h"
namespace func
{
	void printAirlines(const std::vector<AirLine>& vec);
	std::vector<AirLine> firstFunctionality();
	bool �heckLogic(int value);
	int getNumber();
	std::string getString(const std::string& line);
	void secondFunctionality(const std::vector<AirLine>& vecOfAirlines);
	void printInformation();
	void printGuest();
	void firstAttempt();
}