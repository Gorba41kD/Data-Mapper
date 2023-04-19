#include"Person.h"
#include"Passport.h"
#include"Repository.h"
#include"ContainerOfModels.h"
#include"Timer.h"
#include"ThreadPool.h"
template<typename T>
void printInformationAboutModels(std::unique_ptr<Connector>& connector,std::unique_ptr<T>& model,const std::vector<int>& fields)
{
	std::unique_ptr<IRepository<T>> repository = std::make_unique<Repository<T>>(connector);
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
		/*Timer t;
		std::unique_ptr<Connector> connector = std::make_unique<Connector>();
		std::unique_ptr<Person> person = std::make_unique<Person>();
		person->setName("Dzmitry");
		person->setSurname("Harbachyk");
		printInformationAboutModels(connector,person, {Person::PERSON_COUNT});

		std::cout << "===========================================================================" << std::endl;

		std::unique_ptr<Passport> passport = std::make_unique<Passport>();
		passport->setSerialNumber(555111);
		passport->setRegistration("Brest");
		printInformationAboutModels(connector,passport, { Passport::PASSPORT_COUNT});
		std::cout << "Time elapsed: " << t.elapsed() << '\n'; */

		Timer t;
		std::unique_ptr<Connector> connector = std::make_unique<Connector>();

		std::unique_ptr<Person> person = std::make_unique<Person>();
		person->setName("Dzmitry");
		person->setSurname("Harbachyk");
		std::vector<int> attributesOfPerson;
		attributesOfPerson.push_back(Person::PERSON_COUNT);

		std::unique_ptr<Passport> passport = std::make_unique<Passport>();
		passport->setSerialNumber(555111);
		passport->setRegistration("Brest");
		std::vector<int> attributesOfPassport;
		attributesOfPassport.push_back(Passport::PASSPORT_COUNT);

		Thread_pool threadPool(2);
		threadPool.add_task(printInformationAboutModels<Person>, std::ref(connector), std::ref(person), std::ref(attributesOfPerson));
		threadPool.add_task(printInformationAboutModels<Passport>, std::ref(connector), std::ref(passport), std::ref(attributesOfPassport));
		threadPool.wait_all();
		std::cout << "Time elapsed: " << t.elapsed() << '\n';
	}
	catch (std::exception& exc)
	{
		std::cout << exc.what();
	}
	return 0;
}
