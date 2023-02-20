#include "Person.h"
std::istream& operator>>(std::istream& ist, Person& person)
{
    person._name = func::getString("first name");
    person._surname = func::getString("last name");
    return ist;
}
