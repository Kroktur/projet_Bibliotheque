#include "Command.h"
#include <stdexcept>
AddCommand::AddCommand(std::vector<IOperand*> operand):m_operand(operand), m_factory(new AddFactory)
{
}

ICommand* AddCommand::Clone(std::vector<IOperand*> operand)
{
	auto order = operand[0];
	return new AddCommand;
}

void AddCommand::Execute(ConsoleFramebuffer* console, MediaLibrary* library)
{
	console->setString("error not possible to be here", Color::Red, Color::White);
}

AddClient::AddClient(std::vector<IOperand*> operand):m_operand(operand)
{
}

ICommand* AddClient::Clone(std::vector<IOperand*> operand)
{
	return new AddClient{ operand };
}

void AddClient::Execute(ConsoleFramebuffer* console, MediaLibrary* library)
{
	if (m_operand.size() != 5)
	{
		console->setString("Invalid Operand Size", Color::Red, Color::White);
		return;
	}
	if (!(static_cast<StringOperand*>(m_operand[2])->isInt()) || !(static_cast<StringOperand*>(m_operand[4])->isInt()))
	{
		console->setString("Invalid Type of Operand", Color::Red, Color::White);
		return;
	}
	library->addEntity(new Client{ static_cast<StringOperand*>(m_operand[0])->getInformation()
		,static_cast<StringOperand*>(m_operand[1])->getInformation()
		,static_cast<StringOperand*>(m_operand[2])->getInformation()
		,static_cast<StringOperand*>(m_operand[3])->getInformation()
		,static_cast<StringOperand*>(m_operand[4])->getInformation() });
}

AddBook::AddBook(std::vector<IOperand*> operand):m_operand(operand)
{
}

ICommand* AddBook::Clone(std::vector<IOperand*> operand)
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
	library->addEntity(new Book{ static_cast<StringOperand*>(m_operand[0])->getInformation()
		,static_cast<StringOperand*>(m_operand[1])->getInformation()});
}

AddFilm::AddFilm(std::vector<IOperand*> operand):m_operand(operand)
{
}

ICommand* AddFilm::Clone(std::vector<IOperand*> operand)
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
	if (!(static_cast<StringOperand*>(m_operand[2])->isInt()))
	{
		console->setString("Invalid Type of Operand", Color::Red, Color::White);
		return;
	}
	library->addEntity(new Film{ static_cast<StringOperand*>(m_operand[0])->getInformation()
		,static_cast<StringOperand*>(m_operand[1])->getInformation()
		,static_cast<StringOperand*>(m_operand[2])->getInformation() });
}

AddVideoGame::AddVideoGame(std::vector<IOperand*> operand):m_operand(operand)
{
}

ICommand* AddVideoGame::Clone(std::vector<IOperand*> operand)
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
	if (!(static_cast<StringOperand*>(m_operand[2])->isInt()))
	{
		console->setString("Invalid Type of Operand", Color::Red, Color::White);
		return;
	}
	library->addEntity(new VideoGame{ static_cast<StringOperand*>(m_operand[0])->getInformation()
		,static_cast<StringOperand*>(m_operand[1])->getInformation()
		,static_cast<StringOperand*>(m_operand[2])->getInformation()
		,static_cast<StringOperand*>(m_operand[3])->getInformation() });
}

void AddCommand::AddFactory::registertype(std::string str, AddCommand* command)
{
	if (m_factory.contains(str))
		throw std::runtime_error("Key is already registered");
	m_factory.insert({ str, command });
}

ICommand* AddCommand::AddFactory::Create(std::string str, std::vector<IOperand*> operand)
{
	if (auto it = m_factory.find(str); it == m_factory.end())
		throw std::runtime_error("Key is not registered");
	else
		return it->second->Clone(operand);
}
