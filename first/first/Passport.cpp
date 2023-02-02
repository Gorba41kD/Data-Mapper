#include "Passport.h"
std::istream& operator >>(std::istream& ist, Passport& passport)
{

    do
    {
        std::cout << "Please enter your serial_number = ";
        passport._serialNumber = func::getNumber();
    } while (!func::ñheckLogic(passport._serialNumber));

    passport._registration = func::getString("your registration");
    return ist;
}