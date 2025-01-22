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

std::string Book::getISBN() const
{
	return m_ISBN;
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

std::string Film::getSupport() const
{
	return m_Support;
}

std::string Film::getAgeRestriction() const
{
	return m_AgeRestriction;
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
