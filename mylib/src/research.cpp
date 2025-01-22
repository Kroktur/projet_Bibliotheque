#include "research.h"

research::research():m_console(new ConsoleFramebuffer), m_StringManager(new stringInterpreterAndConverter), m_Interpret(new OperandInterpreter(m_console))
{
}

research::~research()
{
	delete m_console;
	m_console = nullptr;

	delete m_StringManager;
	m_StringManager = nullptr;
}

void research::Exe()
{
	while (true)
	{
		m_console->writeConsol();
		m_console->updateSize();
		m_console->show();
		addstring(m_console->getLastCommand());
	}
}

void research::addstring(std::string str)
{
	if (!isNewCommand(str))
		return;
	m_Interpret->interpret(m_StringManager->RemoveEmptySpace(m_StringManager->CreateStringOperand(str)));
}

bool research::isNewCommand(std::string str)
{
	if (m_lastCommand == str || m_StringManager->isEmpty(str))
		return false;
	m_lastCommand = str;
	return true;
}
