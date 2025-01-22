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

ICommand* AddCommand::specialClone(std::vector<StringOperand*> operand)
{
	return m_factory->Create(operand[0]->getInformation(), operand);
}

ICommand* AddCommand::Clone(std::vector<StringOperand*> operand)
{
	AddCommand* mycommand = new AddCommand{ operand };

	return mycommand->specialClone(operand);
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