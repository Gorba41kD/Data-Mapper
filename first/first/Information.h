#pragma once
#include<iostream>
#include"Irepository.h"
class Information
{
	public:
	    int getNumberOfAirLine()const
	    {
	        return _numberOfAirLine;
	    }
	    Information(std::unique_ptr<Irepository>& repository)
	        :_repository(repository)
	    {
	
	    }
	private:
	    int _numberOfAirLine;
	    std::unique_ptr<Irepository>& _repository;
		friend std::istream& operator >>(std::istream& ist, Information& information);
	};
