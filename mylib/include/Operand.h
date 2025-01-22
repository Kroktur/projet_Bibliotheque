#include <string>

enum Operandtype
{
	String_type

};

class IOperand
{
public:
	virtual ~IOperand() = default;
	virtual  Operandtype getType() = 0;
	
};

class StringOperand : public IOperand
{
public:
	StringOperand(std::string information);
	//heritage
	Operandtype getType() override;
	std::string getInformation();
	bool isInt();
private:
	Operandtype m_type;
	std::string m_information;
};