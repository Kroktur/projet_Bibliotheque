#pragma once
#include "Consoleframebuffer.h"
#include "MediathequeV2.h"
#include "Operand.h"

#include <map>
std::vector<StringOperand*> removeFirstOperandIfNotEmpty(std::vector<StringOperand*> operand);
class ICommand
{
public:
	ICommand();
	virtual ~ICommand() = default;
	virtual ICommand* Clone(std::vector<StringOperand*> operand) = 0;
	virtual void Execute(ConsoleFramebuffer* console, MediaLibrary* library) = 0;
};
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