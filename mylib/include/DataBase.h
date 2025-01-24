#pragma once
#include "Consoleframebuffer.h"
#include "interpreter.h"
#include "MediathequeV2.h"
class Database
{
public:
	Database();
	~Database();
	void Exe();
private:
	void addstring(std::string str);
	bool isNewCommand(std::string str);
private:
	ConsoleFramebuffer* m_console;
	stringInterpreterAndConverter* m_StringManager;
	OperandInterpreter* m_Interpret;
	std::string m_lastCommand;
	MediaLibrary* m_Library;
};