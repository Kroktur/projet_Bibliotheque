#include "DataBase.h"

Database::Database():m_console(new ConsoleFramebuffer), m_Library(new MediaLibrary), m_StringManager(new stringInterpreterAndConverter), m_Interpret(new OperandInterpreter(m_console))
{
}

Database::~Database()
{
	// delete all Component
	delete m_console;
	m_console = nullptr;
	delete m_Library;
	m_Library = nullptr;
	delete m_StringManager;
	m_StringManager = nullptr;
	delete m_Interpret;
	m_Interpret = nullptr;
}

void Database::Exe()
{
	m_console->setString("-------New Console-------", Color::Blue, Color::Black);
	//While IsRunning Show in the terminal
	while (m_console->IsRunning())
	{
		m_console->writeConsol();
		m_console->updateSize();
		m_console->show();
		addstring(m_console->getLastCommand());
	}
}

void Database::addstring(std::string str)
{
	if (!isNewCommand(str))
		return;
	m_Interpret->interpret(m_StringManager->RemoveEmptySpace(m_StringManager->CreateStringOperand(str)),m_Library);
}

bool Database::isNewCommand(std::string str)
{
	if (m_lastCommand == str || m_StringManager->isEmpty(str))
		return false;
	m_lastCommand = str;
	return true;
}
