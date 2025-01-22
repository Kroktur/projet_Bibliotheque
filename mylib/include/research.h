#include "Consoleframebuffer.h"
#include "interpreter.h"
class research
{
public:
	research();
	~research();
	void Exe();
private:
	void addstring(std::string str);
	bool isNewCommand(std::string str);
private:
	ConsoleFramebuffer* m_console;
	stringInterpreterAndConverter* m_StringManager;
	OperandInterpreter* m_Interpret;
	std::string m_lastCommand;
};