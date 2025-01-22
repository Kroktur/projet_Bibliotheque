#include "interpreter.h"

stringInterpreterAndConverter::~stringInterpreterAndConverter()
{

}

std::vector<StringOperand*> stringInterpreterAndConverter::CreateStringOperand(std::string str)
{
	std::vector<StringOperand*> myVector;
    std::string workingStr = str;

    while (true)
    {
        auto index = workingStr.find_first_of(' ');
        if (index == std::string::npos)
            break;

        std::string tmp(&workingStr[0], index);
        myVector.push_back(new StringOperand(tmp));
        workingStr = std::string(&workingStr[index + 1], workingStr.size() - (index + 1));
    }
    myVector.push_back(new StringOperand(workingStr));
	return myVector;
}

std::vector<StringOperand*> stringInterpreterAndConverter::RemoveEmptySpace(std::vector<StringOperand*> operand)
{
    std::vector<StringOperand*>  result;
    for (size_t i = 0; i < operand.size(); ++i)
    {
        if (operand[i]->getInformation() != "")
            result.push_back(operand[i]);
    }
    return result;
}

bool stringInterpreterAndConverter::isEmpty(std::string str)
{
	if (str.empty())
		return true;
	for (auto& idx : str)
	{
		if (idx != ' ')
			return false;
	}
	return true;
}

OperandInterpreter::OperandInterpreter(ConsoleFramebuffer* console):m_console(console)
{
}

void OperandInterpreter::interpret(std::vector<StringOperand*> operand)
{
    if (operand[0]->getInformation() != "Hello")
        return;

        m_console->setString("Hello");
        m_console->setString(std::to_string(operand.size()));
}
