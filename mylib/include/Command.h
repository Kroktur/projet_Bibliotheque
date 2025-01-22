#pragma once
#include "Consoleframebuffer.h"
#include "MediathequeV2.h"
#include "Operand.h"

#include <map>
class ICommand
{
public:
	ICommand() = default;
	virtual ~ICommand() = default;
	virtual ICommand* Clone(std::vector<IOperand*> operand) = 0;
	virtual void Execute(ConsoleFramebuffer* console, MediaLibrary* library) = 0;
};
class AddCommand : public ICommand
{
public:
	AddCommand() = default;
	AddCommand(std::vector<IOperand*> operand);
	ICommand* Clone(std::vector<IOperand*> operand) override;
	void Execute(ConsoleFramebuffer* console, MediaLibrary* library) override;
private:
	struct AddFactory
	{
		void registertype(std::string str , AddCommand* command);
		ICommand* Create(std::string str, std::vector<IOperand*> operand);
		std::map<std::string, AddCommand*> m_factory;
	};
	std::vector<IOperand*> m_operand;
	AddFactory* m_factory;
};
class AddClient : public AddCommand
{
public:
	AddClient() = default;
	AddClient(std::vector<IOperand*> operand);
	ICommand* Clone(std::vector<IOperand*> operand) override;
	void Execute(ConsoleFramebuffer* console, MediaLibrary* library) override;
private:
	std::vector<IOperand*> m_operand;

};
class AddBook : public AddCommand
{
public:
	AddBook() = default;
	AddBook(std::vector<IOperand*> operand);
	ICommand* Clone(std::vector<IOperand*> operand) override;
	void Execute(ConsoleFramebuffer* console, MediaLibrary* library) override;
private:
	std::vector<IOperand*> m_operand;

};
class AddFilm : public AddCommand
{
public:
	AddFilm() = default;
	AddFilm(std::vector<IOperand*> operand);
	ICommand* Clone(std::vector<IOperand*> operand) override;
	void Execute(ConsoleFramebuffer* console, MediaLibrary* library) override;
private:
	std::vector<IOperand*> m_operand;

};
class AddVideoGame : public AddCommand
{
public:
	AddVideoGame() = default;
	AddVideoGame(std::vector<IOperand*> operand);
	ICommand* Clone(std::vector<IOperand*> operand) override;
	void Execute(ConsoleFramebuffer* console, MediaLibrary* library) override;
private:
	std::vector<IOperand*> m_operand;

};