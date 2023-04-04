#include"Person.h"
#include"Passport.h"
#include"Repository.h"
#include"ContainerOfModels.h"
template<typename T>
void printInformationAboutModels(std::unique_ptr<T>& model,const std::vector<int>& fields)
{
	std::unique_ptr<IRepository<T>> repository = std::make_unique<Repository<T>>();
	repository->save(model);
	repository->readModel(model,fields);
	std::cout << model;
	auto containerOfModels = repository->readCollections(fields);
	ContainerOfModels<T>::getInstance().setContainer(std::move(containerOfModels));
	ContainerOfModels<T>::getInstance().print();
}
int main()
{
	try 
	{
		std::unique_ptr<Person> person = std::make_unique<Person>();
		person->setName("Dzmitry");
		person->setSurname("Harbachyk");
		printInformationAboutModels(person, {Person::PERSON_COUNT});

		std::cout << "===========================================================================" << std::endl;

		std::unique_ptr<Passport> passport = std::make_unique<Passport>();
		passport->setSerialNumber(555111);
		passport->setRegistration("Brest");
		printInformationAboutModels(passport, { Passport::PASSPORT_COUNT});
	}
	catch (std::exception& exc)
	{
		std::cout << exc.what();
	}
	return 0;
}
