#include "Information.h"
std::istream& operator >>(std::istream& ist, Information& information)
{
	std::cout << "Which airline do you want to chose?" << std::endl;
	information._repository->print();
	auto container = information._repository->get();
	auto begin = container.begin()->second.getId();
	auto end = (--container.end())->second.getId();

	do
	{
		std::cout << "Please Enter a number of airline! = ";

		std::cin >> information._numberOfAirLine;
	} while (information._numberOfAirLine < begin || information._numberOfAirLine > end);
	std::cout << std::endl;
	return ist;
}