#include "Command.h"
#include <stdexcept>

//Global Command
std::vector<StringOperand*> removeFirstOperandIfNotEmpty(std::vector<StringOperand*> operand)
{
	if (operand.size() == 1)
		return operand;
	std::vector<StringOperand*> newOperand;
	for (auto i = 1; i < operand.size(); ++i)
	{
		newOperand.push_back(operand[i]);
	}
	return newOperand;
}
search interpret(StringOperand* operand)
{
	if (operand->getInformation() == "Name")
		return Name_Search;
	if (operand->getInformation() == "FirstName")
		return FirstName_Search;
	if (operand->getInformation() == "Age")
		return Age_Search;
	if (operand->getInformation() == "Email")
		return EmailAddress_Search;
	if (operand->getInformation() == "Phone")
		return PhoneNumber_Search;
	if (operand->getInformation() == "Title")
		return Title_Search;
	if (operand->getInformation() == "ISBN")
		return ISBN_Search;
	if (operand->getInformation() == "Support")
		return Support_Search;
	if (operand->getInformation() == "AgeRestriction")
		return AgeRestriction_Search;
	if (operand->getInformation() == "Studio")
		return Studio_Search;
	if (operand->getInformation() == "Pegi")
		return Pegi_Search;
	if (operand->getInformation() == "Genre")
		return Genre_Search;
	if (operand->getInformation() == "Status")
		return Status_Search;
	return Invalid_Search;
}
//ICommand
ICommand::ICommand()
{
}
//Add Command
AddCommand::AddCommand():m_factory(nullptr)
{

}
AddCommand::AddCommand(std::vector<StringOperand*> operand):m_operand(operand), m_factory(new AddFactory)
{
	m_factory->registertype("Client", new AddClient);
	m_factory->registertype("Book", new AddBook);
	m_factory->registertype("Film", new AddFilm);
	m_factory->registertype("VideoGame", new AddVideoGame);

}
AddCommand::~AddCommand()
{
	delete m_factory;
	m_factory = nullptr;
}
ICommand* AddCommand::specialClone(std::vector<StringOperand*> operand)
{
	return m_factory->Create(operand[0]->getInformation(), operand);
}
ICommand* AddCommand::Clone(std::vector<StringOperand*> operand)
{
	AddCommand* mycommand = new AddCommand{ operand };

	return mycommand->specialClone(operand);
}
void AddCommand::Execute(ConsoleFramebuffer* console, MediaLibrary* library)
{
	console->setString("error not possible to be here", Color::Red, Color::Black);
}
void AddCommand::AddFactory::registertype(std::string str, AddCommand* command)
{
	if (m_factory.contains(str))
		throw std::runtime_error("Key is already registered");
	m_factory.insert({ str, command });
}
ICommand* AddCommand::AddFactory::Create(std::string str, std::vector<StringOperand*> operand)
{
	if (auto it = m_factory.find(str); it == m_factory.end())
		return nullptr;
	else
	{
		operand = removeFirstOperandIfNotEmpty(operand);
		return it->second->Clone(operand);
	}
}
//Add Client
AddClient::AddClient()
{
}
AddClient::AddClient(std::vector<StringOperand*> operand):m_operand(operand)
{
}
ICommand* AddClient::Clone(std::vector<StringOperand*> operand)
{
	return new AddClient{ operand };
}
void AddClient::Execute(ConsoleFramebuffer* console, MediaLibrary* library)
{
	if (m_operand.size() != 5)
	{
		console->setString("Invalid Operand Size Need : Name FirstName Age Email PhoneNumber", Color::Red, Color::Black);
		console->setString("Fail", Color::Red, Color::Black);
		return;
	}
	if (!(m_operand[2]->isInt()) || !(m_operand[4]->isInt()))
	{
		console->setString("Invalid Type of Operand Age And PhoneNumber Cas Contains only Numbers", Color::Red, Color::Black);
		console->setString("Fail", Color::Red, Color::Black);
		return;
	}
	if (library->Search(library->getFullEntitylist(), EmailAddress_Search, m_operand[3]->getInformation()).size() != 0
		|| library->Search(library->getFullEntitylist(), PhoneNumber_Search, m_operand[4]->getInformation()).size() != 0)
	{
		console->setString("Email or PhoneNumber need to be unique", Color::Red, Color::Black);
		console->setString("Fail", Color::Red, Color::Black);
		return;
	}
	library->addEntity(new Client{ m_operand[0]->getInformation()
		,m_operand[1]->getInformation()
		,m_operand[2]->getInformation()
		,m_operand[3]->getInformation()
		,m_operand[4]->getInformation() });
	console->setString("Succes", Color::Green ,Color::Black);
}
// Add Book
AddBook::AddBook()
{
}
AddBook::AddBook(std::vector<StringOperand*> operand):m_operand(operand)
{
}
ICommand* AddBook::Clone(std::vector<StringOperand*> operand)
{
	return new AddBook{ operand };
}
void AddBook::Execute(ConsoleFramebuffer* console, MediaLibrary* library)
{
	if (m_operand.size() != 2)
	{
		console->setString("Invalid Operand Size Need : Title ISBN", Color::Red, Color::Black);
		console->setString("Fail", Color::Red, Color::Black);
		return;
	}
	if (library->Search(library->getFullEntitylist(), ISBN_Search, m_operand[1]->getInformation()).size() != 0)
	{
		console->setString("ISBN need to be unique", Color::Red, Color::Black);
		console->setString("Fail", Color::Red, Color::Black);
		return;
	}
	if (!(m_operand[1]->isInt()))
	{
		console->setString("ISBN Can Contain Only Numbers", Color::Red, Color::Black);
		console->setString("Fail", Color::Red, Color::Black);
		return;
	}
	library->addEntity(new Book{ m_operand[0]->getInformation()
		,m_operand[1]->getInformation()});
	console->setString("Succes", Color::Green, Color::Black);
}
// Add Film
AddFilm::AddFilm()
{
}
AddFilm::AddFilm(std::vector<StringOperand*> operand):m_operand(operand)
{
}
ICommand* AddFilm::Clone(std::vector<StringOperand*> operand)
{
	return new AddFilm{ operand };
}
void AddFilm::Execute(ConsoleFramebuffer* console, MediaLibrary* library)
{
	if (m_operand.size() != 3)
	{
		console->setString("Invalid Operand Size Need : Title Support AgeRestrcition", Color::Red, Color::White);
		console->setString("Fail", Color::Red, Color::Black);
		return;
	}
	if (!(m_operand[2]->isInt()))
	{
		console->setString("AgeRestrcition Can Contain Only Numbers", Color::Red, Color::White);
		console->setString("Fail", Color::Red, Color::Black);
		return;
	}
	library->addEntity(new Film{ m_operand[0]->getInformation()
		,m_operand[1]->getInformation()
		,m_operand[2]->getInformation() });
	console->setString("Succes", Color::Green, Color::Black);
}
//Add VideoGame
AddVideoGame::AddVideoGame()
{
}
AddVideoGame::AddVideoGame(std::vector<StringOperand*> operand):m_operand(operand)
{
}
ICommand* AddVideoGame::Clone(std::vector<StringOperand*> operand)
{
	return new AddVideoGame{ operand };
}
void AddVideoGame::Execute(ConsoleFramebuffer* console, MediaLibrary* library)
{
	if (m_operand.size() != 4)
	{
		console->setString("Invalid Operand Size Need : Title Studio Pegi Gender", Color::Red, Color::White);
		console->setString("Fail", Color::Red, Color::Black);
		return;
	}
	if (!(m_operand[2]->isInt()))
	{
		console->setString("Pegi Can Contain Only Numbers", Color::Red, Color::White);
		console->setString("Fail", Color::Red, Color::Black);
		return;
	}
	library->addEntity(new VideoGame{ m_operand[0]->getInformation()
		,m_operand[1]->getInformation()
		,m_operand[2]->getInformation()
		,m_operand[3]->getInformation() });
	console->setString("Succes", Color::Green, Color::Black);
}
// Show Command
ShowCommand::ShowCommand(std::vector<StringOperand*> operand) :m_operand(operand), m_factory(new ShowFactory)
{
	m_factory->registertype("All", new ShowAll);
	m_factory->registertype("Client", new ShowClient);
	m_factory->registertype("Book", new ShowBook);
	m_factory->registertype("Film", new ShowFilm);
	m_factory->registertype("VideoGame", new ShowVideoGame);
	m_factory->registertype("Media", new ShowMedia);
	m_factory->registertype("Rent", new ShowRentClient); 
}
ShowCommand::ShowCommand() :m_factory(nullptr)
{

}
ShowCommand::~ShowCommand()
{
	delete m_factory;
	m_factory = nullptr;
}
ICommand* ShowCommand::specialClone(std::vector<StringOperand*> operand)
{
	return m_factory->Create(operand[0]->getInformation(), operand);
}

ICommand* ShowCommand::Clone(std::vector<StringOperand*> operand)
{
	ShowCommand* mycommand = new ShowCommand{ operand };

	return mycommand->specialClone(operand);
}
void ShowCommand::Execute(ConsoleFramebuffer* console, MediaLibrary* library)
{
	console->setString("error not possible to be here", Color::Red, Color::White);
}
void ShowCommand::ShowFactory::registertype(std::string str, ShowCommand* command)
{
	if (m_factory.contains(str))
		throw std::runtime_error("Key is already registered");
	m_factory.insert({ str, command });
}
ICommand* ShowCommand::ShowFactory::Create(std::string str, std::vector<StringOperand*> operand)
{
	if (auto it = m_factory.find(str); it == m_factory.end())
		return nullptr;
	else
	{
		operand = removeFirstOperandIfNotEmpty(operand);
		return it->second->Clone(operand);
	}
}
//Show All
ShowAll::ShowAll()
{
}
ShowAll::ShowAll(std::vector<StringOperand*> operand) : m_operand(operand)
{
}
ICommand* ShowAll::Clone(std::vector<StringOperand*> operand)
{
	return new ShowAll{ operand };
}
void ShowAll::Execute(ConsoleFramebuffer* console, MediaLibrary* library)
{
	
	console->setString("Succes", Color::Green, Color::Black);

	library->ShowEntity(library->getFullEntitylist(), console);
}
//Show Client
ShowClient::ShowClient()
{
}
ShowClient::ShowClient(std::vector<StringOperand*> operand) : m_operand(operand)
{
}
ICommand* ShowClient::Clone(std::vector<StringOperand*> operand)
{
	return new ShowClient{ operand };
}
void ShowClient::Execute(ConsoleFramebuffer* console, MediaLibrary* library)
{

	console->setString("Succes", Color::Green, Color::Black);

	library->ShowEntity(library->findType(Client_Type,library->getFullEntitylist()), console);
}
//Show Book
ShowBook::ShowBook()
{
}
ShowBook::ShowBook(std::vector<StringOperand*> operand) : m_operand(operand)
{
}
ICommand* ShowBook::Clone(std::vector<StringOperand*> operand)
{
	return new ShowBook{ operand };
}
void ShowBook::Execute(ConsoleFramebuffer* console, MediaLibrary* library)
{

	console->setString("Succes", Color::Green, Color::Black);

	library->ShowEntity(library->findType(Book_Type, library->getFullEntitylist()), console);
}
//Show Film
ShowFilm::ShowFilm()
{
}
ShowFilm::ShowFilm(std::vector<StringOperand*> operand):m_operand(operand)
{
}
ICommand* ShowFilm::Clone(std::vector<StringOperand*> operand)
{
	return new ShowFilm{ operand };
}
void ShowFilm::Execute(ConsoleFramebuffer* console, MediaLibrary* library)
{

	console->setString("Succes", Color::Green, Color::Black);

	library->ShowEntity(library->findType(Film_Type, library->getFullEntitylist()), console);
}
//Show VideoGame
ShowVideoGame::ShowVideoGame()
{
}
ShowVideoGame::ShowVideoGame(std::vector<StringOperand*> operand) :m_operand(operand)
{
}
ICommand* ShowVideoGame::Clone(std::vector<StringOperand*> operand)
{
	return new ShowVideoGame{ operand };
}
void ShowVideoGame::Execute(ConsoleFramebuffer* console, MediaLibrary* library)
{

	console->setString("Succes", Color::Green, Color::Black);

	library->ShowEntity(library->findType(VideGame_Type, library->getFullEntitylist()), console);
}
//Show All Media
ShowMedia::ShowMedia()
{
}
ShowMedia::ShowMedia(std::vector<StringOperand*> operand) :m_operand(operand)
{
}
ICommand* ShowMedia::Clone(std::vector<StringOperand*> operand)
{
	return new ShowMedia{ operand };
}
void ShowMedia::Execute(ConsoleFramebuffer* console, MediaLibrary* library)
{

	console->setString("Succes", Color::Green, Color::Black);
	auto list1 = library->findType(VideGame_Type, library->getFullEntitylist());
	auto list2 = library->findType(Film_Type, library->getFullEntitylist());
	auto list3 = library->findType(Book_Type, library->getFullEntitylist());
	library->ShowEntity(library->conbineList(library->conbineList(list1, list2), list3), console);
}
// Show Rent
ShowRentClient::ShowRentClient()
{
}
ShowRentClient::ShowRentClient(std::vector<StringOperand*> operand) :m_operand(operand)
{
}
ICommand* ShowRentClient::Clone(std::vector<StringOperand*> operand)
{
	return new ShowRentClient{ operand };;
}
void ShowRentClient::Execute(ConsoleFramebuffer* console, MediaLibrary* library)
{
	if (m_operand.size() < 2)
	{
		console->setString("Invalid Operand Size Need : Argument Research  ... ", Color::Red, Color::White);
		console->setString("Fail", Color::Red, Color::Black);
		return;
	}
	std::vector<Entity*> clientlist;
	clientlist = library->Search(library->getFullEntitylist(), interpret(m_operand[0]), m_operand[1]->getInformation());

	if (m_operand.size() % 2 != 0)
	{
		console->setString("Invalid Operand Size Need : Argument Reasearch ...", Color::Red, Color::Black);
		console->setString("Fail", Color::Red, Color::Black);
		return;
	}
	if (m_operand.size() >= 2)
	{
		clientlist = library->Search(library->getFullEntitylist(), interpret(m_operand[0]), m_operand[1]->getInformation());
	}
	if (m_operand.size() > 2)
	{
		for (auto i = 2; i < m_operand.size(); i += 2)
		{
			clientlist = library->FilterList(clientlist, library->Search(library->getFullEntitylist(), interpret(m_operand[i]), m_operand[i + 1]->getInformation()));
		}
	}
	if (clientlist.empty())
	{
		console->setString(" No Client Found", Color::Red, Color::Black);
		console->setString("Fail", Color::Red, Color::Black);
		return;
	}
	if (clientlist.size() != 1)
	{
		console->setString("Too Much Client Found", Color::Red, Color::White);
		console->setString("Fail", Color::Red, Color::Black);
		return;
	}
	if (clientlist[0]->getType() != Client_Type)
	{
		console->setString("No Client Found", Color::Red, Color::White);
		console->setString("Fail", Color::Red, Color::Black);
		return;
	}
	console->setString("Succes", Color::Green, Color::Black);
	library->ShowEntity(static_cast<Client*>(clientlist[0])->getMedia(), console);
}
//ReSearch Command
ReSearch::ReSearch()
{
}
ReSearch::ReSearch(std::vector<StringOperand*> operand) :m_operand(operand)
{
}
ICommand* ReSearch::Clone(std::vector<StringOperand*> operand)
{
	return new ReSearch{ operand };
}
void ReSearch::Execute(ConsoleFramebuffer* console, MediaLibrary* library)
{
	std::vector<Entity*> list;
	if (m_operand.size() < 2)
	{
		console->setString("Invalid Operand Size Need : Argument Research  ... ", Color::Red, Color::White);
		console->setString("Fail", Color::Red, Color::Black);
		return;
	}
	if (m_operand.size() % 2 != 0)
	{
		console->setString("Invalid Operand Size Need : Argument Research  ... ", Color::Red, Color::White);
		console->setString("Fail", Color::Red, Color::Black);
		return;
	}
	if (m_operand.size() >= 2)
	{
		list = library->Search(library->getFullEntitylist(), interpret(m_operand[0]), m_operand[1]->getInformation());
	}
	if (m_operand.size() > 2)
	{
		for (auto i = 2; i < m_operand.size(); i += 2)
		{
			list = library->FilterList(list, library->Search(library->getFullEntitylist(), interpret(m_operand[i]), m_operand[i + 1]->getInformation()));
		}
	}
	if (list.empty())
	{
		console->setString("Nothing Found", Color::Red, Color::Black);
		console->setString("Fail", Color::Red, Color::Black);
		return;
	}
	console->setString("Succes", Color::Green, Color::Black);
	library->ShowEntity(list, console);
}
// Rent Command
RentMedia::RentMedia()
{
}
RentMedia::RentMedia(std::vector<StringOperand*> operand) :m_operand(operand)
{
}
ICommand* RentMedia::Clone(std::vector<StringOperand*> operand)
{
	return new RentMedia{ operand };
}
void RentMedia::Execute(ConsoleFramebuffer* console, MediaLibrary* library)
{
	if (m_operand.size() < 4)
	{
		console->setString("Invalid Operand Size Need :Argument(Client) Research(Client) Argument(Media) Research(Media)  ... ", Color::Red, Color::White);
		console->setString("Fail", Color::Red, Color::Black);
		return;
	}
	std::vector<Entity*> list;
	std::vector<Entity*> clientlist;
	clientlist = library->Search(library->getFullEntitylist(), interpret(m_operand[0]), m_operand[1]->getInformation());
	
	if (m_operand.size() % 2 != 0)
	{
		console->setString("Invalid Operand Size Need :Argument(Client) Research(Client) Argument(Media) Research(Media)  ... ", Color::Red, Color::White);
		console->setString("Fail", Color::Red, Color::Black);
		return;
	}
	if (m_operand.size() >= 4)
	{
		list = library->Search(library->getFullEntitylist(), interpret(m_operand[2]), m_operand[3]->getInformation());
	}
	if (m_operand.size() >4)
	{
		for (auto i = 4; i < m_operand.size(); i += 2)
		{
			list = library->FilterList(list, library->Search(library->getFullEntitylist(), interpret(m_operand[i]), m_operand[i + 1]->getInformation()));
		}
	}
	if (clientlist.empty())
	{
		console->setString(" No Client Found", Color::Red, Color::Black);
		console->setString("Fail", Color::Red, Color::Black);
		return;
	}
	if (clientlist.size() != 1)
	{
		console->setString("Too Much Client Found", Color::Red, Color::White);
		console->setString("Fail", Color::Red, Color::Black);
		return;
	}
	if (clientlist[0]->getType() != Client_Type)
	{
		console->setString("No Client Found", Color::Red, Color::White);
		console->setString("Fail", Color::Red, Color::Black);
		return;
	}
	if (list.empty())
	{
		console->setString(" No Media Found", Color::Red, Color::Black);
		console->setString("Fail", Color::Red, Color::Black);
		return;
	}
	
	console->setString("Succes", Color::Green, Color::Black);
	library->rentMedia(static_cast<Client*>(clientlist[0]), list);
}
//Return Command
ReturnMedia::ReturnMedia()
{
}
ReturnMedia::ReturnMedia(std::vector<StringOperand*> operand) :m_operand(operand)
{
}
ICommand* ReturnMedia::Clone(std::vector<StringOperand*> operand)
{
	return new ReturnMedia{ operand };
}
void ReturnMedia::Execute(ConsoleFramebuffer* console, MediaLibrary* library)
{
	if (m_operand.size() < 4)
	{
		console->setString("Invalid Operand Size Need :Argument(Client) Research(Client) Argument(Media) Research(Media)  ... ", Color::Red, Color::White);
		console->setString("Fail", Color::Red, Color::Black);
		return;
	}
	if (m_operand.size() % 2 != 0)
	{
		console->setString("Invalid Operand Size Need :Argument(Client) Research(Client) Argument(Media) Research(Media)  ... ", Color::Red, Color::White);
		console->setString("Fail", Color::Red, Color::Black);
		return;
	}
	std::vector<Entity*> list;
	std::vector<Entity*> clientlist;
	clientlist = library->Search(library->getFullEntitylist(), interpret(m_operand[0]), m_operand[1]->getInformation());
	if (m_operand.size() >= 4)
	{
		list = library->Search(library->getFullEntitylist(), interpret(m_operand[2]), m_operand[3]->getInformation());
	}
	if (m_operand.size() > 4)
	{
		for (auto i = 4; i < m_operand.size(); i += 2)
		{
			list = library->FilterList(list, library->Search(library->getFullEntitylist(), interpret(m_operand[i]), m_operand[i + 1]->getInformation()));
		}
	}
	if (clientlist.empty())
	{
		console->setString(" No Client Found", Color::Red, Color::Black);
		console->setString("Fail", Color::Red, Color::Black);
		return;
	}
	if (clientlist.size() != 1)
	{
		console->setString("Too Much Client Found", Color::Red, Color::White);
		console->setString("Fail", Color::Red, Color::Black);
		return;
	}
	if (clientlist[0]->getType() != Client_Type)
	{
		console->setString("No Client Found", Color::Red, Color::White);
		console->setString("Fail", Color::Red, Color::Black);
		return;
	}
	if (list.empty())
	{
		console->setString(" No Media Found", Color::Red, Color::Black);
		console->setString("Fail", Color::Red, Color::Black);
		return;
	}
	console->setString("Succes", Color::Green, Color::Black);
	library->returnMedia(static_cast<Client*>(clientlist[0]), list);
}
//Remove Command
RemoveCommand::RemoveCommand()
{
}
RemoveCommand::RemoveCommand(std::vector<StringOperand*> operand):m_operand(operand)
{
}
ICommand* RemoveCommand::Clone(std::vector<StringOperand*> operand)
{
	return new RemoveCommand(operand);
}
void RemoveCommand::Execute(ConsoleFramebuffer* console, MediaLibrary* library)
{
	std::vector<Entity*> list;
	if (m_operand.size() < 2)
	{
		console->setString("Invalid Operand Size Need :Argument Research  ... ", Color::Red, Color::White);
		console->setString("Fail", Color::Red, Color::Black);
		return;
	}
	if (m_operand.size() % 2 != 0)
	{
		console->setString("Invalid Operand Size Need :Argument Research  ... ", Color::Red, Color::White);
		console->setString("Fail", Color::Red, Color::Black);
		return;
	}
	if (m_operand.size() >= 2)
	{
		list = library->Search(library->getFullEntitylist(), interpret(m_operand[0]), m_operand[1]->getInformation());
	}
	if (m_operand.size() > 2)
	{
		for (auto i = 2; i < m_operand.size(); i += 2)
		{
			list = library->FilterList(list, library->Search(library->getFullEntitylist(), interpret(m_operand[i]), m_operand[i + 1]->getInformation()));
		}
	}
	if (list.empty())
	{
		console->setString("Nothing Found Imposible to Remove", Color::Red, Color::Black);
		console->setString("Fail", Color::Red, Color::Black);
		return;
	}
	console->setString("Succes", Color::Green, Color::Black);
	library->removeEntity(list);
}
// Clear Command
clearCommand::clearCommand()
{
}
clearCommand::clearCommand(std::vector<StringOperand*> operand):m_operand(operand)
{
}
ICommand* clearCommand::Clone(std::vector<StringOperand*> operand)
{
	return new clearCommand(operand);
}
void clearCommand::Execute(ConsoleFramebuffer* console, MediaLibrary* library)
{
	console->clear();
	console->setString("---Clear Succes---", Color::Green, Color::Black);
	console->setString("-------New Consol-------", Color::Blue, Color::Black);
}
//Help Command
HelpCommand::HelpCommand()
{
}
HelpCommand::HelpCommand(std::vector<StringOperand*> operand):m_operand(operand)
{
}
ICommand* HelpCommand::Clone(std::vector<StringOperand*> operand)
{
	return new HelpCommand(operand);
}
void HelpCommand::Execute(ConsoleFramebuffer* console, MediaLibrary* library)
{
	console->setString("---Help---", Color::Blue, Color::Black);
	//Global information
	console->setString("---Global Information ---", Color::Blue, Color::Black);
	console->setString("Important: <> Are used to represent commands but are recognized as words", Color::Red, Color::Black);
	console->setString(" Exemple <Show> : Use it like this : Show", Color::Green, Color::Black);
	// Argument Method
	console->setString("Important: to write and search words with spaces you need \" <word with space> \" And Respect Space", Color::Red, Color::Black);
	console->setString(" Exemple : \"Le Super Livre Titi\"", Color::Green, Color::Black);
	//Base Command
	console->setString("---Base Command---", Color::Blue, Color::Black);
	console->setString("Base Command : <Add> <Show> <Search> <Rent> <Return> <Remove> <Clear> <Exit> ", Color::Blue, Color::Black);
	console->setString(" Exemple : Add ....", Color::Green, Color::Black);
	// Argument Method
	console->setString("--- Argument search Method --- ", Color::Blue, Color::Black);
	console->setString("Important: Argument search method is used in several places  ", Color::Red, Color::Black);
	// Argument Method
	console->setString(" Argument search Method: Works in pairs infinitely you need 1 Argument and 1 Personnal Search ", Color::Blue, Color::Black);
	console->setString(" Argument : <Name> <FirstName> <Age> <Email> <Phone> <Title> <ISBN> <Support> <AgeRestriction> <Studio> <Pegi> <Genre> <Status>", Color::Blue, Color::Black);
	console->setString(" Important: <Status> recognize only 2 Word : Available / Borrowed  ", Color::Red, Color::Black);
	console->setString(" Exemple : Command Name Arthur FirstName Blanchet Age 19 ...", Color::Green, Color::Black);
	//Add
	console->setString("---Add--- ", Color::Blue, Color::Black);
	console->setString("Add Command : <Client> <Book> <Film> <VideoGame> ", Color::Blue, Color::Black);
	// Add
	console->setString("Client Command : Name FirstName Age Email PhoneNumber", Color::Blue, Color::Black);
	console->setString("Book Command : Title ISBN", Color::Blue, Color::Black);
	console->setString("Film Command : Title Support AgeRestriction ", Color::Blue, Color::Black);
	console->setString("VideoGame Command : Title Studio Pegi Genre ", Color::Blue, Color::Black);
	console->setString(" Exemple : Add Client Arthur Blanchet 18 ablanchet@gaming.tech 06435065## ", Color::Green, Color::Black);
	// Show
	console->setString("---Show--- ", Color::Blue, Color::Black);
	console->setString("Show Command : <Client> <Book> <Film> <VideoGame> <Media> <All> ", Color::Blue, Color::Black);
	console->setString(" Exemple : Show All ", Color::Green, Color::Black);
	//Search
	console->setString("---Search--- ", Color::Blue, Color::Black);
	//Search
	console->setString(" Use Argument search", Color::Red, Color::Black);
	console->setString(" Exemple : Search Title EldenRing Status Available ", Color::Green, Color::Black);
	// Rent
	console->setString("---Rent--- ", Color::Blue, Color::Black);
	console->setString(" Use Argument search", Color::Red, Color::Black);
	console->setString("Rend Command: First Argument Search For Client Search other For Media ", Color::Blue, Color::Black);
	console->setString(" Exemple : Rent Name Arthur Title EldenRing Status Available ...", Color::Green, Color::Black);
	//return
	console->setString("---Return--- ", Color::Blue, Color::Black);
	console->setString(" Use Argument search", Color::Red, Color::Black);
	console->setString("Return Command: First Argument Search For Client Search other For Media ", Color::Blue, Color::Black);
	console->setString(" Exemple : Return Name Arthur Title EldenRing Status Available ...", Color::Green, Color::Black);
	//remove
	console->setString("---Remove--- ", Color::Blue, Color::Black);
	console->setString(" Use Argument search", Color::Red, Color::Black);
	console->setString(" Exemple : Remove Name Arthur FirstName Blanchet ...", Color::Green, Color::Black);
	//Clear
	console->setString("---Clear--- ", Color::Blue, Color::Black);
	console->setString(" Use : Clear ", Color::Green, Color::Black);
	//Exit
	console->setString("---Exit--- ", Color::Blue, Color::Black);
	console->setString(" Use : Exit ", Color::Green, Color::Black);
}
//Exit Command
ExitCommand::ExitCommand()
{
}
ExitCommand::ExitCommand(std::vector<StringOperand*> operand):m_operand(operand)
{
}
ICommand* ExitCommand::Clone(std::vector<StringOperand*> operand)
{
	return new ExitCommand(operand);
}
void ExitCommand::Execute(ConsoleFramebuffer* console, MediaLibrary* library)
{
	console->CloseWindow();
}


