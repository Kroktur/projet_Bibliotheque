#include "Operand.h"

StringOperand::StringOperand(std::string information):m_type(String_type),m_information(information)
{
}

Operandtype StringOperand::gettype()
{
    return m_type;
}

std::string StringOperand::getinformation()
{
    return m_information;
}
