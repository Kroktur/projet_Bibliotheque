#include "Operand.h"

StringOperand::StringOperand(std::string information):m_type(String_type),m_information(information)
{
}

Operandtype StringOperand::getType()
{
    return m_type;
}

std::string StringOperand::getInformation()
{
    return m_information;
}

bool StringOperand::isInt()
{
    if (m_information.empty())
        return false;
    for (auto i = 0; i < m_information.size(); ++i)
    {
        if (!std::isdigit(m_information[i]))
            return false;
    }
    return true;
}
