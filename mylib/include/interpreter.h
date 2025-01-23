#pragma once
#include "Operand.h"
#include "Consoleframebuffer.h"
#include "MediathequeV2.h"
#include <vector>
#include <map>
#include "Command.h"
class stringInterpreterAndConverter
{
public:
	~stringInterpreterAndConverter();
	std::vector<StringOperand*> CreateStringOperand(std::string str);
	std::vector<StringOperand*> RemoveEmptySpace(std::vector<StringOperand*> operand);
	bool isEmpty(std::string str);
private:
};

class OperandInterpreter
{
public:
	OperandInterpreter(ConsoleFramebuffer* console);
	~OperandInterpreter();
	void interpret(std::vector<StringOperand*> operand, MediaLibrary* library);
private:
	struct IComandFactory
	{
		void registertype(std::string str, ICommand* command);
		ICommand* Create(std::string str, std::vector<StringOperand*> operand);
		std::map<std::string, ICommand*> m_factory;
	};
	ConsoleFramebuffer* m_console;
	IComandFactory* m_factory;
};