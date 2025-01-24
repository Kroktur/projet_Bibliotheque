#pragma once
#include "Consoleframebuffer.h"
#include "MediathequeV2.h"
#include "Operand.h"
#include <map>

// Global Founction
std::vector<StringOperand*> removeFirstOperandIfNotEmpty(std::vector<StringOperand*> operand);
search interpret(StringOperand* operand);

//Interface
class ICommand
{
public:
	ICommand();
	virtual ~ICommand() = default;
	virtual ICommand* Clone(std::vector<StringOperand*> operand) = 0;
	virtual void Execute(ConsoleFramebuffer* console, MediaLibrary* library) = 0;
};
//ADD Command
class AddCommand : public ICommand
{
public:
	AddCommand();
	AddCommand(std::vector<StringOperand*> operand);

	~AddCommand();
	ICommand* specialClone(std::vector<StringOperand*> operand);
	ICommand* Clone(std::vector<StringOperand*> operand) override;
	void Execute(ConsoleFramebuffer* console, MediaLibrary* library) override;
private:
	struct AddFactory
	{
		void registertype(std::string str , AddCommand* command);
		ICommand* Create(std::string str, std::vector<StringOperand*> operand);
		std::map<std::string, AddCommand*> m_factory;
	};
	std::vector<StringOperand*> m_operand;
	AddFactory* m_factory;
};
class AddClient : public AddCommand
{
public:
	AddClient();
	AddClient(std::vector<StringOperand*> operand);
	ICommand* Clone(std::vector<StringOperand*> operand) override;
	void Execute(ConsoleFramebuffer* console, MediaLibrary* library) override;
private:
	std::vector<StringOperand*> m_operand;

};
class AddBook : public AddCommand
{
public:
	AddBook();
	AddBook(std::vector<StringOperand*> operand);
	ICommand* Clone(std::vector<StringOperand*> operand) override;
	void Execute(ConsoleFramebuffer* console, MediaLibrary* library) override;
private:
	std::vector<StringOperand*> m_operand;

};
class AddFilm : public AddCommand
{
public:
	AddFilm() ;
	AddFilm(std::vector<StringOperand*> operand);
	ICommand* Clone(std::vector<StringOperand*> operand) override;
	void Execute(ConsoleFramebuffer* console, MediaLibrary* library) override;
private:
	std::vector<StringOperand*> m_operand;

};
class AddVideoGame : public AddCommand
{
public:
	AddVideoGame();
	AddVideoGame(std::vector<StringOperand*> operand);
	ICommand* Clone(std::vector<StringOperand*> operand) override;
	void Execute(ConsoleFramebuffer* console, MediaLibrary* library) override;
private:
	std::vector<StringOperand*> m_operand;
	
};
//ShowCommand
class ShowCommand : public ICommand
{
public:
	ShowCommand();
	ShowCommand(std::vector<StringOperand*> operand);
	~ShowCommand();
	ICommand* specialClone(std::vector<StringOperand*> operand);
	ICommand* Clone(std::vector<StringOperand*> operand) override;
	void Execute(ConsoleFramebuffer* console, MediaLibrary* library) override;
private:
	struct ShowFactory
	{
		void registertype(std::string str, ShowCommand* command);
		ICommand* Create(std::string str, std::vector<StringOperand*> operand);
		std::map<std::string, ShowCommand*> m_factory;
	};
	std::vector<StringOperand*> m_operand;
	ShowFactory* m_factory;
};
class ShowAll : public ShowCommand
{
public:
	ShowAll();
	ShowAll(std::vector<StringOperand*> operand);
	ICommand* Clone(std::vector<StringOperand*> operand) override;
	void Execute(ConsoleFramebuffer* console, MediaLibrary* library) override;
private:
	std::vector<StringOperand*> m_operand;

};
class ShowClient : public ShowCommand
{
public:
	ShowClient();
	ShowClient(std::vector<StringOperand*> operand);
	ICommand* Clone(std::vector<StringOperand*> operand) override;
	void Execute(ConsoleFramebuffer* console, MediaLibrary* library) override;
private:
	std::vector<StringOperand*> m_operand;

};
class ShowBook : public ShowCommand
{
public:
	ShowBook();
	ShowBook(std::vector<StringOperand*> operand);
	ICommand* Clone(std::vector<StringOperand*> operand) override;
	void Execute(ConsoleFramebuffer* console, MediaLibrary* library) override;
private:
	std::vector<StringOperand*> m_operand;

};
class ShowFilm : public ShowCommand
{
public:
	ShowFilm();
	ShowFilm(std::vector<StringOperand*> operand);
	ICommand* Clone(std::vector<StringOperand*> operand) override;
	void Execute(ConsoleFramebuffer* console, MediaLibrary* library) override;
private:
	std::vector<StringOperand*> m_operand;

};
class ShowVideoGame : public ShowCommand
{
public:
	ShowVideoGame();
	ShowVideoGame(std::vector<StringOperand*> operand);
	ICommand* Clone(std::vector<StringOperand*> operand) override;
	void Execute(ConsoleFramebuffer* console, MediaLibrary* library) override;
private:
	std::vector<StringOperand*> m_operand;

};
class ShowMedia : public ShowCommand
{
public:
	ShowMedia();
	ShowMedia(std::vector<StringOperand*> operand);
	ICommand* Clone(std::vector<StringOperand*> operand) override;
	void Execute(ConsoleFramebuffer* console, MediaLibrary* library) override;
private:
	std::vector<StringOperand*> m_operand;

};
class ShowRentClient : public ShowCommand
{
public:
	ShowRentClient();
	ShowRentClient(std::vector<StringOperand*> operand);
	ICommand* Clone(std::vector<StringOperand*> operand) override;
	void Execute(ConsoleFramebuffer* console, MediaLibrary* library) override;
private:
	std::vector<StringOperand*> m_operand;

};
// ReSearch Command
class ReSearch : public ICommand
{
public:
	ReSearch();
	ReSearch(std::vector<StringOperand*> operand);
	ICommand* Clone(std::vector<StringOperand*> operand) override;
	void Execute(ConsoleFramebuffer* console, MediaLibrary* library) override;
private:
	

	std::vector<StringOperand*> m_operand;
};	
// Rent Command
class RentMedia : public ICommand
{
public:
	RentMedia();
	RentMedia(std::vector<StringOperand*> operand);
	ICommand* Clone(std::vector<StringOperand*> operand) override;
	void Execute(ConsoleFramebuffer* console, MediaLibrary* library) override;
private:


	std::vector<StringOperand*> m_operand;
};
//Return Command
class ReturnMedia : public ICommand
{
public:
	ReturnMedia();
	ReturnMedia(std::vector<StringOperand*> operand);
	ICommand* Clone(std::vector<StringOperand*> operand) override;
	void Execute(ConsoleFramebuffer* console, MediaLibrary* library) override;
private:


	std::vector<StringOperand*> m_operand;
};
//Remove Command
class RemoveCommand : public ICommand
{
public:
	RemoveCommand();
	RemoveCommand(std::vector<StringOperand*> operand);
	ICommand* Clone(std::vector<StringOperand*> operand) override;
	void Execute(ConsoleFramebuffer* console, MediaLibrary* library) override;
private:


	std::vector<StringOperand*> m_operand;

};
//Clear Command
class clearCommand : public ICommand
{
public:
	clearCommand();
	clearCommand(std::vector<StringOperand*> operand);
	ICommand* Clone(std::vector<StringOperand*> operand) override;
	void Execute(ConsoleFramebuffer* console, MediaLibrary* library) override;
private:


	std::vector<StringOperand*> m_operand;
};
//Help Command
class HelpCommand : public ICommand
{
public:
	HelpCommand();
	HelpCommand(std::vector<StringOperand*> operand);
	ICommand* Clone(std::vector<StringOperand*> operand) override;
	void Execute(ConsoleFramebuffer* console, MediaLibrary* library) override;
private:


	std::vector<StringOperand*> m_operand;
};
//Exit Command
class ExitCommand : public ICommand
{
public:
	ExitCommand();
	ExitCommand(std::vector<StringOperand*> operand);
	ICommand* Clone(std::vector<StringOperand*> operand) override;
	void Execute(ConsoleFramebuffer* console, MediaLibrary* library) override;
private:


	std::vector<StringOperand*> m_operand;
};