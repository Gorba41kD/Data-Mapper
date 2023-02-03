#include"Repository.h"
#include"enum_Program.h"
namespace pro
{
    void printGuest()
    {
        std::map<int, AirLine> mapOfAirlines;
        int value = 0;
        std::unique_ptr<Irepository> repository = std::make_unique<Repository>();
        do
        {
            std::cout << "Please Enter 1 to see all list or 2 to add a new passage or 3 to quit the program" << std::endl;
            value = func::getNumber();
            system("cls");
            mapOfAirlines = repository->read();
            if (value == FIRST_CASE)
            {
                repository->print();
            }
            if (value == SECOND_CASE)
            {
                Passport passport;
                std::cin >> passport;
                Person person;
                std::cin >> person;
                Information information(repository);
                std::cin >> information;
                repository->save(passport);
                repository->save(person);
                repository->save(information);

            }
            if (value == THIRD_CASE)
            {
                std::cout << "You quit the program" << std::endl;
                return;
            }
        } while (true);
    }
    void secondAttempt()
    {
        std::string login;
        bool success = false;
        std::string password;
        do
        {
            system("cls");
            std::cout << "Enter login = guest: " << std::endl;
            std::cin >> login;
            std::cout << std::endl;
            std::cout << "Enter password = quest: " << std::endl;
            std::cin >> password;
            std::cout << std::endl;
            if (login == "guest" && password == "guest")
            {
                success = true;
                std::cout << "Welcome " << login << "!!!" << std::endl << std::endl;
                try
                {
                    printGuest();
                }
                catch (const std::exception& e)
                {
                    std::cerr << e.what() << std::endl;
                }
                catch (...)
                {
                    std::cerr << "catch (...)" << std::endl;
                }
            }
            else if (login == "admin" && password == "1111")
            {
                success = true;
                std::cout << "Welcome " << login << "!!!" << std::endl << std::endl;

                try
                {
                    std::unique_ptr<Irepository> repository = std::make_unique<Repository>();
                    repository->printInformation();
                }
                catch (const std::exception& e)
                {
                    std::cerr << e.what() << std::endl;
                }
                catch (...)
                {
                    std::cerr << "catch (...)" << std::endl;
                }
            }
        } while (!success);
    }
}
