#include "Command.h"
#include <stdexcept>
std::vector<StringOperand*> removeFirstOperandIfNotEmpty(std::vector<StringOperand*> operand)
{
	if (operand.size() == 1)
		return operand;
	std::vector<StringOperand*> newOperand;
	for (auto i = 1; i < operand.size(); ++i)
	{
		newOperand.push_back(operand[i]);
	}
	return newOperand;
}
AddCommand::AddCommand():m_factory(new AddFactory)
{

}
AddCommand::AddCommand(std::vector<StringOperand*> operand):m_operand(operand), m_factory(new AddFactory)
{
	m_factory->registertype("Client", new AddClient);
	m_factory->registertype("Book", new AddBook);
	m_factory->registertype("Film", new AddFilm);
	m_factory->registertype("VideoGame", new AddVideoGame);

}

AddCommand::~AddCommand()
{
	delete m_factory;
	m_factory = nullptr;
}

ICommand* AddCommand::specialClone(std::vector<StringOperand*> operand, AddCommand* comand)
{
	delete comand;
	return m_factory->Create(operand[0]->getInformation(), operand);
}

ICommand* AddCommand::Clone(std::vector<StringOperand*> operand)
{
	AddCommand* mycommand = new AddCommand{ operand };

	return mycommand->specialClone(operand, mycommand);
}

void AddCommand::Execute(ConsoleFramebuffer* console, MediaLibrary* library)
{
	console->setString("error not possible to be here", Color::Red, Color::White);
}

AddClient::AddClient()
{
}

AddClient::AddClient(std::vector<StringOperand*> operand):m_operand(operand)
{
}

ICommand* AddClient::Clone(std::vector<StringOperand*> operand)
{
	return new AddClient{ operand };
}

void AddClient::Execute(ConsoleFramebuffer* console, MediaLibrary* library)
{
	if (m_operand.size() != 5)
	{
		console->setString("Invalid Operand Size", Color::Red, Color::Black);
		return;
	}
	if (!(m_operand[2]->isInt()) || !(m_operand[4]->isInt()))
	{
		console->setString("Invalid Type of Operand", Color::Red, Color::Black);
		return;
	}
	if (library->Search(library->getFullEntitylist(), EmailAddress_Search, m_operand[3]->getInformation()).size() != 0
		|| library->Search(library->getFullEntitylist(), PhoneNumber_Search, m_operand[4]->getInformation()).size() != 0)
	{
		console->setString("Email or Phone need to be unique", Color::Red, Color::Black);
		return;
	}
	library->addEntity(new Client{ m_operand[0]->getInformation()
		,m_operand[1]->getInformation()
		,m_operand[2]->getInformation()
		,m_operand[3]->getInformation()
		,m_operand[4]->getInformation() });
	console->setString("Client Added", Color::Green ,Color::Black);
}

AddBook::AddBook()
{
}

AddBook::AddBook(std::vector<StringOperand*> operand):m_operand(operand)
{
}

ICommand* AddBook::Clone(std::vector<StringOperand*> operand)
{
	return new AddBook{ operand };
}

void AddBook::Execute(ConsoleFramebuffer* console, MediaLibrary* library)
{
	if (m_operand.size() != 2)
	{
		console->setString("Invalid Operand Size", Color::Red, Color::White);
		return;
	}
	if (library->Search(library->getFullEntitylist(), ISBN_Search, m_operand[1]->getInformation()).size() != 0)
	{
		console->setString("ISBN need to be unique", Color::Red, Color::Black);
		return;
	}
	library->addEntity(new Book{ m_operand[0]->getInformation()
		,m_operand[1]->getInformation()});
	console->setString("Book Added", Color::Green, Color::Black);
}

AddFilm::AddFilm()
{
}

AddFilm::AddFilm(std::vector<StringOperand*> operand):m_operand(operand)
{
}

ICommand* AddFilm::Clone(std::vector<StringOperand*> operand)
{
	return new AddFilm{ operand };
}

void AddFilm::Execute(ConsoleFramebuffer* console, MediaLibrary* library)
{
	if (m_operand.size() != 3)
	{
		console->setString("Invalid Operand Size", Color::Red, Color::White);
		return;
	}
	if (!(m_operand[2]->isInt()))
	{
		console->setString("Invalid Type of Operand", Color::Red, Color::White);
		return;
	}
	library->addEntity(new Film{ m_operand[0]->getInformation()
		,m_operand[1]->getInformation()
		,m_operand[2]->getInformation() });
	console->setString("Film Added", Color::Green, Color::Black);
}

AddVideoGame::AddVideoGame()
{
}

AddVideoGame::AddVideoGame(std::vector<StringOperand*> operand):m_operand(operand)
{
}

ICommand* AddVideoGame::Clone(std::vector<StringOperand*> operand)
{
	return new AddVideoGame{ operand };
}

void AddVideoGame::Execute(ConsoleFramebuffer* console, MediaLibrary* library)
{
	if (m_operand.size() != 4)
	{
		console->setString("Invalid Operand Size", Color::Red, Color::White);
		return;
	}
	if (!(m_operand[2]->isInt()))
	{
		console->setString("Invalid Type of Operand", Color::Red, Color::White);
		return;
	}
	library->addEntity(new VideoGame{ m_operand[0]->getInformation()
		,m_operand[1]->getInformation()
		,m_operand[2]->getInformation()
		,m_operand[3]->getInformation() });
	console->setString("VideoGame Added", Color::Green, Color::Black);
}





ICommand::ICommand()
{
}
void AddCommand::AddFactory::registertype(std::string str, AddCommand* command)
{
	if (m_factory.contains(str))
		throw std::runtime_error("Key is already registered");
	m_factory.insert({ str, command });
}
ICommand* AddCommand::AddFactory::Create(std::string str, std::vector<StringOperand*> operand)
{

	if (auto it = m_factory.find(str); it == m_factory.end())
		return nullptr;
	else
	{
		operand = removeFirstOperandIfNotEmpty(operand);
		return it->second->Clone(operand);
	}
}

ShowCommand::ShowCommand(std::vector<StringOperand*> operand) :m_operand(operand), m_factory(new ShowFactory)
{
	m_factory->registertype("All", new ShowAll);
	m_factory->registertype("Client", new ShowClient);
	m_factory->registertype("Book", new ShowBook);
	m_factory->registertype("Film", new ShowFilm);
	m_factory->registertype("VideoGame", new ShowVideoGame);
	m_factory->registertype("Media", new ShowMedia);
	m_factory->registertype("Rent", new ShowRentClient); 
}

ShowCommand::~ShowCommand()
{
	delete m_factory;
	m_factory = nullptr;
}

ICommand* ShowCommand::specialClone(std::vector<StringOperand*> operand)
{
	return m_factory->Create(operand[0]->getInformation(), operand);
}

ICommand* ShowCommand::Clone(std::vector<StringOperand*> operand)
{
	ShowCommand* mycommand = new ShowCommand{ operand };

	return mycommand->specialClone(operand);
}

void ShowCommand::Execute(ConsoleFramebuffer* console, MediaLibrary* library)
{
	console->setString("error not possible to be here", Color::Red, Color::White);
}
void ShowCommand::ShowFactory::registertype(std::string str, ShowCommand* command)
{
	if (m_factory.contains(str))
		throw std::runtime_error("Key is already registered");
	m_factory.insert({ str, command });
}
ICommand* ShowCommand::ShowFactory::Create(std::string str, std::vector<StringOperand*> operand)
{

	if (auto it = m_factory.find(str); it == m_factory.end())
		return nullptr;
	else
	{
		operand = removeFirstOperandIfNotEmpty(operand);
		return it->second->Clone(operand);
	}
}

ShowCommand::ShowCommand() :m_factory(new ShowFactory)
{

}



ShowAll::ShowAll()
{
}

ShowAll::ShowAll(std::vector<StringOperand*> operand) : m_operand(operand)
{
}

ICommand* ShowAll::Clone(std::vector<StringOperand*> operand)
{
	return new ShowAll{ operand };
}

void ShowAll::Execute(ConsoleFramebuffer* console, MediaLibrary* library)
{
	
	console->setString("Show all Entity :", Color::Green, Color::Black);

	library->ShowEntity(library->getFullEntitylist(), console);
}

ShowClient::ShowClient()
{
}

ShowClient::ShowClient(std::vector<StringOperand*> operand) : m_operand(operand)
{
}

ICommand* ShowClient::Clone(std::vector<StringOperand*> operand)
{
	return new ShowClient{ operand };
}

void ShowClient::Execute(ConsoleFramebuffer* console, MediaLibrary* library)
{

	console->setString("Show Client :", Color::Green, Color::Black);

	library->ShowEntity(library->findType(Client_Type,library->getFullEntitylist()), console);
}
ShowBook::ShowBook()
{
}

ShowBook::ShowBook(std::vector<StringOperand*> operand) : m_operand(operand)
{
}

ICommand* ShowBook::Clone(std::vector<StringOperand*> operand)
{
	return new ShowBook{ operand };
}

void ShowBook::Execute(ConsoleFramebuffer* console, MediaLibrary* library)
{

	console->setString("Show Book :", Color::Green, Color::Black);

	library->ShowEntity(library->findType(Book_Type, library->getFullEntitylist()), console);
}
ShowFilm::ShowFilm()
{
}

ShowFilm::ShowFilm(std::vector<StringOperand*> operand):m_operand(operand)
{
}


ICommand* ShowFilm::Clone(std::vector<StringOperand*> operand)
{
	return new ShowFilm{ operand };
}

void ShowFilm::Execute(ConsoleFramebuffer* console, MediaLibrary* library)
{

	console->setString("Show Film :", Color::Green, Color::Black);

	library->ShowEntity(library->findType(Film_Type, library->getFullEntitylist()), console);
}
ShowVideoGame::ShowVideoGame()
{
}

ShowVideoGame::ShowVideoGame(std::vector<StringOperand*> operand) :m_operand(operand)
{
}


ICommand* ShowVideoGame::Clone(std::vector<StringOperand*> operand)
{
	return new ShowVideoGame{ operand };
}

void ShowVideoGame::Execute(ConsoleFramebuffer* console, MediaLibrary* library)
{

	console->setString("Show VideoGame :", Color::Green, Color::Black);

	library->ShowEntity(library->findType(VideGame_Type, library->getFullEntitylist()), console);
}
ShowMedia::ShowMedia()
{
}

ShowMedia::ShowMedia(std::vector<StringOperand*> operand) :m_operand(operand)
{
}


ICommand* ShowMedia::Clone(std::vector<StringOperand*> operand)
{
	return new ShowMedia{ operand };
}

void ShowMedia::Execute(ConsoleFramebuffer* console, MediaLibrary* library)
{

	console->setString("Show Media :", Color::Green, Color::Black);
	auto list1 = library->findType(VideGame_Type, library->getFullEntitylist());
	auto list2 = library->findType(Film_Type, library->getFullEntitylist());
	auto list3 = library->findType(Book_Type, library->getFullEntitylist());
	library->ShowEntity(library->conbineList(library->conbineList(list1, list2), list3), console);
}
ReSearch::ReSearch()
{
}

ReSearch::ReSearch(std::vector<StringOperand*> operand) :m_operand(operand)
{
}


ICommand* ReSearch::Clone(std::vector<StringOperand*> operand)
{
	return new ReSearch{ operand };
}

void ReSearch::Execute(ConsoleFramebuffer* console, MediaLibrary* library)
{
	std::vector<Entity*> list;
	if (m_operand.size() < 2)
	{
		console->setString("Invalid Operand Size", Color::Red, Color::White);
		return;
	}
	if (m_operand.size() % 2 != 0)
	{
		console->setString("Invalid Operand Size", Color::Red, Color::Black);
		return;
	}
	if (m_operand.size() >= 2)
	{
		list = library->Search(library->getFullEntitylist(), interpret(m_operand[0]), m_operand[1]->getInformation());
	}
	if (m_operand.size() > 2)
	{
		for (auto i = 2; i < m_operand.size(); i += 2)
		{
			list = library->FilterList(list, library->Search(library->getFullEntitylist(), interpret(m_operand[i]), m_operand[i + 1]->getInformation()));
		}
	}
	


	if (list.empty())
	{
		console->setString("Not Found", Color::Red, Color::Black);
		return;
	}
	console->setString("ReaSearch", Color::Green, Color::Black);
	library->ShowEntity(list, console);
}

search interpret(StringOperand* operand)
{
	if (operand->getInformation() == "Name")
		return Name_Search;
	if (operand->getInformation() == "FirstName")
		return FirstName_Search;
	if (operand->getInformation() == "Age")
		return Age_Search;
	if (operand->getInformation() == "EmailAddress")
		return EmailAddress_Search;
	if (operand->getInformation() == "PhoneNumber")
		return PhoneNumber_Search;
	if (operand->getInformation() == "Title")
		return Title_Search;
	if (operand->getInformation() == "ISBN")
		return ISBN_Search;
	if (operand->getInformation() == "Support")
		return Support_Search;
	if (operand->getInformation() == "AgeRestriction")
		return AgeRestriction_Search;
	if (operand->getInformation() == "Studio")
		return Studio_Search;
	if (operand->getInformation() == "Pegi")
		return Pegi_Search;
	if (operand->getInformation() == "Gender")
		return Gender_Search;
	if (operand->getInformation() == "Status")
		return Status_Search;
	return Invalid_Search;
}
RentMedia::RentMedia()
{
}

RentMedia::RentMedia(std::vector<StringOperand*> operand) :m_operand(operand)
{
}


ICommand* RentMedia::Clone(std::vector<StringOperand*> operand)
{
	return new RentMedia{ operand };
}

void RentMedia::Execute(ConsoleFramebuffer* console, MediaLibrary* library)
{
	if (m_operand.size() < 4)
	{
		console->setString("Invalid Operand Size", Color::Red, Color::White);
		return;
	}

	std::vector<Entity*> list;
	std::vector<Entity*> clientlist;
	clientlist = library->Search(library->getFullEntitylist(), interpret(m_operand[0]), m_operand[1]->getInformation());
	
	if (m_operand.size() % 2 != 0)
	{
		console->setString("Invalid Operand Size", Color::Red, Color::Black);
		return;
	}
	
	if (m_operand.size() >= 4)
	{
		list = library->Search(library->getFullEntitylist(), interpret(m_operand[2]), m_operand[3]->getInformation());
	}
	if (m_operand.size() >4)
	{
		for (auto i = 4; i < m_operand.size(); i += 2)
		{
			list = library->FilterList(list, library->Search(library->getFullEntitylist(), interpret(m_operand[i]), m_operand[i + 1]->getInformation()));
		}
	}
	if (clientlist.size() != 1)
	{
		console->setString("Too Much Client Found", Color::Red, Color::White);
		return;
	}
	if (list.empty())
	{
		console->setString("Medi Not Found", Color::Red, Color::Black);
		return;
	}

	console->setString("rentMedia", Color::Green, Color::Black);
	library->rentMedia(static_cast<Client*>(clientlist[0]), list);
	library->ShowEntity(static_cast<Client*>(clientlist[0])->getMedia(),console);
}
ReturnMedia::ReturnMedia()
{
}

ReturnMedia::ReturnMedia(std::vector<StringOperand*> operand) :m_operand(operand)
{
}


ICommand* ReturnMedia::Clone(std::vector<StringOperand*> operand)
{
	return new ReturnMedia{ operand };
}

void ReturnMedia::Execute(ConsoleFramebuffer* console, MediaLibrary* library)
{
	if (m_operand.size() < 4)
	{
		console->setString("Invalid Operand Size", Color::Red, Color::Black);
		return;
	}
	if (m_operand.size() % 2 != 0)
	{
		console->setString("Invalid Operand Size", Color::Red, Color::Black);
		return;
	}
	std::vector<Entity*> list;
	std::vector<Entity*> clientlist;
	clientlist = library->Search(library->getFullEntitylist(), interpret(m_operand[0]), m_operand[1]->getInformation());
	


	if (m_operand.size() >= 4)
	{
		list = library->Search(library->getFullEntitylist(), interpret(m_operand[2]), m_operand[3]->getInformation());
	}
	if (m_operand.size() > 4)
	{
		for (auto i = 4; i < m_operand.size(); i += 2)
		{
			list = library->FilterList(list, library->Search(library->getFullEntitylist(), interpret(m_operand[i]), m_operand[i + 1]->getInformation()));
		}
	}
	if (clientlist.size() != 1)
	{
		console->setString("Too Much Client Found", Color::Red, Color::White);
		return;
	}
	if (list.empty())
	{
		console->setString("Medi Not Found", Color::Red, Color::Black);
		return;
	}

	console->setString("ReturnMedia", Color::Green, Color::Black);
	library->returnMedia(static_cast<Client*>(clientlist[0]), list);
	library->ShowEntity(static_cast<Client*>(clientlist[0])->getMedia(), console);
}

ShowRentClient::ShowRentClient()
{
}

ShowRentClient::ShowRentClient(std::vector<StringOperand*> operand):m_operand(operand)
{
}

ICommand* ShowRentClient::Clone(std::vector<StringOperand*> operand)
{
	return new ShowRentClient{ operand };;
}

void ShowRentClient::Execute(ConsoleFramebuffer* console, MediaLibrary* library)
{
	if (m_operand.size() < 2)
	{
		console->setString("Invalid Operand Size", Color::Red, Color::White);
		return;
	}
	std::vector<Entity*> clientlist;
	clientlist = library->Search(library->getFullEntitylist(), interpret(m_operand[0]), m_operand[1]->getInformation());
	
	if (m_operand.size() % 2 != 0)
	{
		console->setString("Invalid Operand Size", Color::Red, Color::Black);
		return;
	}
	if (m_operand.size() >= 2)
	{
		clientlist = library->Search(library->getFullEntitylist(), interpret(m_operand[0]), m_operand[1]->getInformation());
	}
	if (m_operand.size() > 2)
	{
		for (auto i = 2; i < m_operand.size(); i += 2)
		{
			clientlist = library->FilterList(clientlist, library->Search(library->getFullEntitylist(), interpret(m_operand[i]), m_operand[i + 1]->getInformation()));
		}
	}
	if (clientlist.size() != 1)
	{
		console->setString("Too Much Client Found", Color::Red, Color::White);
		return;
	}
	if (clientlist.empty())
	{
		console->setString(" Client Not Found", Color::Red, Color::Black);
		return;
	}
	console->setString("Show Client Rent ", Color::Green, Color::Black);
	library->ShowEntity(static_cast<Client*>(clientlist[0])->getMedia(), console);
}

RemoveCommand::RemoveCommand()
{
}

RemoveCommand::RemoveCommand(std::vector<StringOperand*> operand):m_operand(operand)
{
}

ICommand* RemoveCommand::Clone(std::vector<StringOperand*> operand)
{
	return new RemoveCommand(operand);
}

void RemoveCommand::Execute(ConsoleFramebuffer* console, MediaLibrary* library)
{
	std::vector<Entity*> list;
	if (m_operand.size() < 2)
	{
		console->setString("Invalid Operand Size", Color::Red, Color::White);
		return;
	}
	if (m_operand.size() % 2 != 0)
	{
		console->setString("Invalid Operand Size", Color::Red, Color::Black);
		return;
	}
	if (m_operand.size() >= 2)
	{
		list = library->Search(library->getFullEntitylist(), interpret(m_operand[0]), m_operand[1]->getInformation());
	}
	if (m_operand.size() > 2)
	{
		for (auto i = 2; i < m_operand.size(); i += 2)
		{
			list = library->FilterList(list, library->Search(library->getFullEntitylist(), interpret(m_operand[i]), m_operand[i + 1]->getInformation()));
		}
	}



	if (list.empty())
	{
		console->setString("Not Found Imposible to remove", Color::Red, Color::Black);
		return;
	}

	console->setString("Remove Done", Color::Green, Color::Black);
	library->removeEntity(list);
}

clearCommand::clearCommand()
{
}

clearCommand::clearCommand(std::vector<StringOperand*> operand):m_operand(operand)
{
}

ICommand* clearCommand::Clone(std::vector<StringOperand*> operand)
{
	return new clearCommand(operand);
}

void clearCommand::Execute(ConsoleFramebuffer* console, MediaLibrary* library)
{
	if (m_operand.size() !=1 )
	{
		console->setString("Invalid Operand Size", Color::Red, Color::White);
		return;
	}
	console->clear();
	console->setString("---Clear Succes---", Color::Green, Color::Black);
	console->setString("-------New Consol-------", Color::Blue, Color::Black);
}

ExitCommand::ExitCommand()
{
}

ExitCommand::ExitCommand(std::vector<StringOperand*> operand):m_operand(operand)
{
}

ICommand* ExitCommand::Clone(std::vector<StringOperand*> operand)
{
	return new ExitCommand(operand);
}

void ExitCommand::Execute(ConsoleFramebuffer* console, MediaLibrary* library)
{
	console->setString("Close Consol", Color::Red, Color::Black);
	console->CloseWindow();
}
