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
        // Recherche du premier espace ou guillemet
        auto spaceIndex = workingStr.find_first_of(' ');
        auto quoteIndex = workingStr.find_first_of('"');

        // Si on trouve un guillemet avant un espace, on prend la chaîne jusqu'au prochain guillemet
        if (quoteIndex != std::string::npos && (spaceIndex == std::string::npos || quoteIndex < spaceIndex))
        {
            // Trouver la position du guillemet fermant
            auto closingQuoteIndex = workingStr.find_first_of('"', quoteIndex + 1);
            if (closingQuoteIndex != std::string::npos)
            {
                // Extraire la chaîne entre guillemets
                std::string tmp = workingStr.substr(quoteIndex + 1, closingQuoteIndex - quoteIndex - 1);
                myVector.push_back(new StringOperand(tmp));
                // Mettre à jour workingStr pour continuer après le guillemet fermant
                workingStr = workingStr.substr(closingQuoteIndex + 1);
            }
            else
            {
                // Si un guillemet ouvrant est trouvé sans guillemet fermant, on arrête.
                break;
            }
        }
        else if (spaceIndex != std::string::npos)
        {
            // Sinon, si un espace est trouvé, prendre la chaîne avant l'espace
            std::string tmp = workingStr.substr(0, spaceIndex);
            myVector.push_back(new StringOperand(tmp));
            // Mettre à jour workingStr pour continuer après l'espace
            workingStr = workingStr.substr(spaceIndex + 1);
        }
        else
        {
            // Si il n'y a plus d'espace ou de guillemet, on ajoute le reste de la chaîne
            myVector.push_back(new StringOperand(workingStr));
            break;
        }
    }

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
        m_console->setString("InvalidCommand : Add ... Show ... Search... Rent... Return ... Remove... Clear Exit", Color::Blue, Color::Black);
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
