#include "interpreter.h"
#include <stdexcept>
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

OperandInterpreter::OperandInterpreter(ConsoleFramebuffer* console):m_console(console), m_factory(new IComandFactory)
{
    m_factory->registertype("Add", new AddCommand);
    m_factory->registertype("Show", new ShowCommand);
    m_factory->registertype("Search", new ReSearch);
    m_factory->registertype("Rent", new RentMedia);
    m_factory->registertype("Return", new ReturnMedia);
    m_factory->registertype("Remove", new RemoveCommand); 
        m_factory->registertype("Clear", new clearCommand);
        m_factory->registertype("Exit", new ExitCommand);
}

OperandInterpreter::~OperandInterpreter()
{
    delete m_factory;
    m_factory = nullptr;
}

void OperandInterpreter::interpret(std::vector<StringOperand*> operand,MediaLibrary* library)
{
    if (operand[0]->getInformation() == "Hello")
    {
        m_console->setString("Hello");
        m_console->setString(std::to_string(operand.size()));
    }
    auto* object = m_factory->Create(operand[0]->getInformation(), operand);
    if (object == nullptr)
    {
        m_console->setString("InvalidCommand", Color::Blue, Color::Black);
        return;
    }
    object->Execute(m_console, library);
    delete object;
    object = nullptr;
    
}

void OperandInterpreter::IComandFactory::registertype(std::string str, ICommand* command)
{
    if (m_factory.contains(str))
        throw std::runtime_error("Key is already registered");
    m_factory.insert({ str, command });
}

ICommand* OperandInterpreter::IComandFactory::Create(std::string str, std::vector<StringOperand*> operand)
{
    if (auto it = m_factory.find(str); it == m_factory.end())
        return nullptr;
    else
    {
        operand = removeFirstOperandIfNotEmpty(operand);
        return it->second->Clone(operand);
    }
}
