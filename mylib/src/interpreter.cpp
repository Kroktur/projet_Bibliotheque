#include "interpreter.h"
#include <stdexcept>
stringInterpreterAndConverter::~stringInterpreterAndConverter()
{

}

std::vector<StringOperand*> stringInterpreterAndConverter::CreateStringOperand(std::string str)
{
    std::vector<StringOperand*> myVector;
    std::string workingStr = str;
    // split text into words
    while (true)
    {
        auto spaceIndex = workingStr.find_first_of(' ');
        auto quoteIndex = workingStr.find_first_of('"');

        if (quoteIndex != std::string::npos && (spaceIndex == std::string::npos || quoteIndex < spaceIndex))
        {
            auto closingQuoteIndex = workingStr.find_first_of('"', quoteIndex + 1);
            if (closingQuoteIndex != std::string::npos)
            {
                std::string tmp = workingStr.substr(quoteIndex + 1, closingQuoteIndex - quoteIndex - 1);
                myVector.push_back(new StringOperand(tmp));
                workingStr = workingStr.substr(closingQuoteIndex + 1);
            }
            else
            {
                break;
            }
        }
        else if (spaceIndex != std::string::npos)
        {
            std::string tmp = workingStr.substr(0, spaceIndex);
            myVector.push_back(new StringOperand(tmp));
            workingStr = workingStr.substr(spaceIndex + 1);
        }
        else
        {
            myVector.push_back(new StringOperand(workingStr));
            break;
        }
    }
    return myVector;
}

std::vector<StringOperand*> stringInterpreterAndConverter::RemoveEmptySpace(std::vector<StringOperand*> operand)
{
    // remove empty words
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
        m_factory->registertype("Help", new HelpCommand);
}

OperandInterpreter::~OperandInterpreter()
{
    //delete the factory at the end
    delete m_factory;
    m_factory = nullptr;
}

void OperandInterpreter::interpret(std::vector<StringOperand*> operand,MediaLibrary* library)
{
    auto* object = m_factory->Create(operand[0]->getInformation(), operand);
    if (object == nullptr)
    {
        //error
        m_console->setString("InvalidCommand : Tape Help for help", Color::Blue, Color::Black);
        m_console->setString("Fail", Color::Red, Color::Black);
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
