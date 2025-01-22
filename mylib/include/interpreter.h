#pragma once
#include "Operand.h"
#include "Consoleframebuffer.h"
#include <vector>
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
	void interpret(std::vector<StringOperand*> operand);
private:
	ConsoleFramebuffer* m_console;
};