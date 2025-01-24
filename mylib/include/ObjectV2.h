#pragma once
#include <string>
#include <vector>
#include "Consoleframebuffer.h"
enum search
{
	Invalid_Search
	,Name_Search
	, FirstName_Search
	,Age_Search
	,EmailAddress_Search
	,PhoneNumber_Search
	,Title_Search
	,ISBN_Search
	,Support_Search
	,AgeRestriction_Search
	,Studio_Search
	,Pegi_Search
	,Genre_Search
	,Status_Search
};
enum Entity_Type
{
	Media_Type
	,Individuals_Type
	,Client_Type
	,Book_Type
	,Film_Type
	,VideGame_Type
};
enum Media_Status
{
	Invalid_Status
	,Available_Status
	,Borrowed_Status
};
class Entity
{
public:
	Entity(Entity_Type type);
	virtual ~Entity() = default;
	virtual Entity_Type getType() const= 0;
	virtual void Render(ConsoleFramebuffer* consol) = 0;
protected:
	Entity_Type m_Type;
};
class IIndividuals : public Entity
{
public:
	IIndividuals(std::string Name, std::string FirstName, std::string Age, std::string emailAddress, std::string PhoneNumber, Entity_Type Type);
	Entity_Type getType() const override;
	virtual std::string getName() const = 0;
	virtual std::string getFirstName() const = 0;
	virtual std::string getAge() const = 0;
	virtual std::string getEmailAddress() const = 0;
	virtual std::string getPhoneNumber() const = 0;
	virtual void Render(ConsoleFramebuffer* consol) = 0;
protected:
	std::string m_Name;
	std::string m_FirstName;
	std::string m_Age;
	std::string m_EmailAddress;
	std::string m_PhoneNumber;
};
class IMedia;
class Client : public IIndividuals
{
public:
	//impl
	Client(std::string Name, std::string FirstName , std::string Age, std::string emailAddress, std::string PhoneNumber);
	std::string getName() const override;
	std::string getFirstName() const override;
	std::string getAge() const override;
	std::string getEmailAddress() const override;
	std::string getPhoneNumber() const override;
	void rentMedia(std::vector<Entity*> list);
	std::vector<Entity*> getMedia();
	void removeMedia(Entity* entity);
	virtual void Render(ConsoleFramebuffer* consol);
	bool operator ==(Client& client);
private:
	std::vector<Entity*> m_RentMedia;
};
class IMedia : public Entity
{
public:

	IMedia(std::string Title, Entity_Type Type);
	Entity_Type getType() const override;
	virtual std::string getTitle() const = 0;
	virtual Media_Status getMediaStatus() const = 0;
	virtual void changeStatus(Media_Status newstatus) = 0;
	virtual void Render(ConsoleFramebuffer* consol) = 0;
protected:
	std::string m_Title;
	Media_Status m_Status;
};
class Book : public IMedia
{
public:
	Book(std::string Title, std::string ISBN);
	std::string getTitle() const override;
	Media_Status getMediaStatus() const override;
	void changeStatus(Media_Status newstatus) override;
	virtual void Render(ConsoleFramebuffer* consol);
	std::string getISBN() const;
	bool operator ==(Book& book);
private:	
	std::string m_ISBN;
};
class Film : public IMedia
{
public:
	Film(std::string Title, std::string support, std::string agerestriction);
	std::string getTitle() const override;
	Media_Status getMediaStatus() const override;
	void changeStatus(Media_Status newstatus) override;
	virtual void Render(ConsoleFramebuffer* consol);
	std::string getSupport() const ;
	std::string getAgeRestriction() const ;
	bool operator ==(Film& film);
private:
	std::string m_Support;
	std::string m_AgeRestriction;
};
class VideoGame : public IMedia
{
public:
	VideoGame(std::string Title, std::string studio, std::string pegi, std::string gender);
	std::string getTitle() const override;
	Media_Status getMediaStatus() const override;
	void changeStatus(Media_Status newstatus) override;
	virtual void Render(ConsoleFramebuffer* consol);
	std::string getStudio();
	std::string getPegi();
	std::string getGenre();
	bool operator ==(VideoGame& VideoGame);
private:
	std::string m_Studio;
	std::string m_Pegi;
	std::string m_Genre;
};