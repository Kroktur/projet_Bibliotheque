#include "ObjectV2.h"
//Entity

Entity::Entity(Entity_Type type):m_Type(type)
{
}
// IIndividuals

IIndividuals::IIndividuals(std::string Name, std::string FirstName, std::string Age, std::string emailAddress, std::string PhoneNumber, Entity_Type Type):
	m_Name(Name)
	, m_FirstName(FirstName)
	, m_Age(Age)
	, m_EmailAddress(emailAddress)
	, m_PhoneNumber(PhoneNumber)
	, Entity(Type)
{}
Entity_Type IIndividuals::getType() const
{
	return m_Type;
}
// Client 
Client::Client(std::string Name, std::string FirstName, std::string Age, std::string emailAddress, std::string PhoneNumber):
	IIndividuals(Name, FirstName, Age, emailAddress, PhoneNumber, Client_Type)
{
}

std::string Client::getName() const 
{
	return m_Name;
}

std::string Client::getFirstName() const
{
	return m_FirstName;
}

std::string Client::getAge() const
{
	return m_Age;
}

std::string Client::getEmailAddress() const
{
	return m_EmailAddress;
}

std::string Client::getPhoneNumber() const
{
	return m_PhoneNumber;
}
void Client::Render(ConsoleFramebuffer* consol)
{
	//type
	consol->setString("---Client---",Color::White,Color::Black);
	//name
	consol->setString("---Name---", Color::Blue);
	consol->setString(m_Name);
	//firstName
	consol->setString("---FirstName---", Color::Blue);
	consol->setString(m_FirstName);
	//age
	consol->setString("---Age---");
	consol->setString(m_Age);
	//address
	consol->setString("---EmailAddress---", Color::Blue);
	consol->setString(m_EmailAddress);
	//phoneNumber
	consol->setString("---PhoneNumber---", Color::Blue);
	consol->setString(m_PhoneNumber);
}
bool Client::operator==(Client& client)
{
	if (m_Name != client.getName())
		return false;
	if (m_FirstName != client.getFirstName())
		return false;
	if (m_Age != client.getAge())
		return false;
	if (m_EmailAddress != client.getEmailAddress())
		return false;
	if (m_PhoneNumber != client.getPhoneNumber())
		return false;
	return true;
}
//IMedia

IMedia::IMedia(std::string Title, Entity_Type Type):
	m_Title(Title)
	,m_Status(Available_Status)
	,Entity(Type)
{}

Entity_Type IMedia::getType() const
{
	return m_Type;
}
// Book
Book::Book(std::string Title, std::string ISBN):
	m_ISBN(ISBN)
	, IMedia(Title,Book_Type)
{}

std::string Book::getTitle() const
{
	return m_Title;
}

Media_Status Book::getMediaStatus() const
{
	return m_Status;
}

void Book::changeStatus(Media_Status newstatus)
{
	m_Status = newstatus;
}

void Book::Render(ConsoleFramebuffer* consol)
{
	//type
	consol->setString("---Book---", Color::White, Color::Black);
	//Title
	consol->setString("---Title---", Color::Blue);
	consol->setString(m_Title);
	//ISBN
	consol->setString("---ISBN---", Color::Blue);
	consol->setString(m_ISBN);
	//status
	consol->setString("---Status---", Color::Blue);
	if(m_Status == Available_Status)
		consol->setString("Available",Color::Green);
	if (m_Status == Borrowed_Status)
		consol->setString("Borrowed", Color::Red);
}

std::string Book::getISBN() const
{
	return m_ISBN;
}

bool Book::operator==(Book& book)
{
	if (m_Title != book.getTitle())
		return false;
	if (m_ISBN != book.getISBN())
		return false;
	return true;
}

Film::Film(std::string Title, std::string support, std::string agerestriction):
	m_Support(support)
	,m_AgeRestriction(agerestriction)
	, IMedia(Title,Film_Type)
{}

std::string Film::getTitle() const
{
	return m_Title;
}

Media_Status Film::getMediaStatus() const
{
	return m_Status;
}
void Film::changeStatus(Media_Status newstatus)
{
	m_Status = newstatus;
}

void Film::Render(ConsoleFramebuffer* consol)
{
	//type
	consol->setString("---Book---", Color::White, Color::Black);
	//Title
	consol->setString("---Title---",Color::Blue);
	consol->setString(m_Title);
	//Support
	consol->setString("---Support---", Color::Blue);
	consol->setString(m_Support);
	//Agerestriction
	consol->setString("---AgeRestriction---", Color::Blue);
	consol->setString(m_AgeRestriction);
	//status
	consol->setString("---Status---", Color::Blue);
	if (m_Status == Available_Status)
		consol->setString("Available", Color::Green);
	if (m_Status == Borrowed_Status)
		consol->setString("Borrowed", Color::Red);
}

std::string Film::getSupport() const
{
	return m_Support;
}

std::string Film::getAgeRestriction() const
{
	return m_AgeRestriction;
}

bool Film::operator==(Film& film)
{
	if (m_Title != film.getTitle())
		return false;
	if (m_AgeRestriction != film.getAgeRestriction())
		return false;
	if (m_Support != film.getSupport())
		return false;
	return true;
}

VideoGame::VideoGame(std::string Title, std::string studio, std::string pegi, std::string gender):
m_Studio(studio)
,m_Pegi(pegi)
,m_Gender(gender)
,IMedia(Title,VideGame_Type)
{}

std::string VideoGame::getTitle() const
{
	return m_Title;
}

Media_Status VideoGame::getMediaStatus() const
{
	return m_Status;
}

void VideoGame::changeStatus(Media_Status newstatus)
{
	m_Status = newstatus;
}

void VideoGame::Render(ConsoleFramebuffer* consol)
{
	//type
	consol->setString("---Book---", Color::White, Color::Black);
	//Title
	consol->setString("---Title---",Color::Blue);
	consol->setString(m_Title);
	//Studio
	consol->setString("---Studio---", Color::Blue);
	consol->setString(m_Studio);
	//Pegi
	consol->setString("---Pegi---", Color::Blue);
	consol->setString(m_Pegi);
	//Gender
	consol->setString("---Gender---", Color::Blue);
	consol->setString(m_Gender);
	//status
	consol->setString("---Status---", Color::Blue);
	if (m_Status == Available_Status)
		consol->setString("Available", Color::Green);
	if (m_Status == Borrowed_Status)
		consol->setString("Borrowed", Color::Red);
}

std::string VideoGame::getStudio()
{
	return m_Studio;
}

std::string VideoGame::getPegi()
{
	return m_Pegi;
}

std::string VideoGame::getGender()
{
	return m_Gender;
}

bool VideoGame::operator==(VideoGame& VideoGame)
{
	if (m_Title != VideoGame.getTitle())
		return false;
	if (m_Studio != VideoGame.getStudio())
		return false;
	if (m_Pegi != VideoGame.getPegi())
		return false;
	if (m_Gender != VideoGame.getGender())
		return false;
	return true;
}
