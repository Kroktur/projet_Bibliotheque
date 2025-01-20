#pragma once
#pragma once
#include <string>
#include <vector>
class Media;
enum object_type
{
	Client_type
	, Media_type
};

enum Mediatype
{
	book
	, film
	, game
};

enum status
{
	available
	, borrowed
	, unavailable
};
enum Film_Support
{
	blue_ray
	, DVD
	, Digital
};
enum game_Studio
{
	Ubisoft
	, Unreal
	, RSI
};
enum game_gender
{
	fps
	, mmo
};
class Object
{
public:
	virtual ~Object() = default;
	virtual object_type gettype() = 0;
protected:
	object_type m_type;
};

class Client :public Object
{
public:
	Client(std::string name, std::string firstname, int age, std::string address, std::string phoneNumber)
		:m_name(name)
		, m_firstname(firstname)
		, m_age(age)
		, m_address(address)
		, m_phoneNumber(phoneNumber)
	{
		m_type = Client_type;
	}
	~Client()
	{
	}
	//implementation
	object_type gettype() override { return m_type; }
	//name
	void changename(std::string newname) { m_name = newname; }
	std::string& getname() { return m_name; }
	//firstname
	void changefirstname(std::string newfirstname) { m_firstname = newfirstname; }
	std::string& getfirstname() { return m_firstname; }
	//age
	void changeage(int newage) { m_age = newage; }
	int getage() { return m_age; }
	//address
	void changeaddress(std::string newaddress) { m_address = newaddress; }
	std::string& getaddress() { return m_address; }
	//phoneNumber
	void changephoneNumber(std::string newphoneNumber) { m_phoneNumber = newphoneNumber; }
	std::string& getphoneNumber() { return m_phoneNumber; }
	// rent media
	void addmedia(Media* media){m_rent.push_back(media);}
	void removemedia(Media* media)
	{
		for (auto it = m_rent.begin(); it != m_rent.end();)
		{
			if (*it == media)
			{
				it = m_rent.erase(it);
				break;
			}
			else
			{
				++it;
			}
		}
	}
	std::vector<Media*> getmediarent() { return m_rent; }
private:
	std::string m_name;
	std::string m_firstname;
	int m_age;
	std::string m_address;
	std::string m_phoneNumber;
	std::vector<Media*> m_rent;

	/*std::vector<Media> m_emprund;*/
};
class Media :public Object
{
public:
	Media() { m_type = Media_type; m_status = available; }
	//implementation
	object_type gettype() override { return m_type; }
	//Mediatype
	virtual Mediatype getMediatype() = 0;
	virtual std::string& getTitle() = 0;
	virtual status getStatus() = 0;
protected:
	status m_status;
	Mediatype m_mediatype;
	std::string m_title;
};
class Book : public Media
{
public:
	Book(std::string Title, std::string ISBN) :m_ISBN(ISBN) { m_mediatype = book;  m_title = Title; }
	//implementation
	Mediatype getMediatype() override { return m_mediatype; }
	std::string& getTitle() override { return m_title; }
	status getStatus() override { return m_status; }
	//Title
	void changeTitle(std::string& newTitle) { m_title = newTitle; }
	//Status
	void changeStatus(status newstatus) { m_status = newstatus; }
	//ISBN
	void changeISBN(std::string& newTitle) { m_ISBN = newTitle; }
	std::string& getISBN() { return m_ISBN; }
private:
	std::string m_ISBN;
};
class Film : public Media
{
public:
	Film(std::string Title, Film_Support support, int agerestriction) :m_support(support), m_agerestriction(agerestriction) { m_mediatype = film;  m_title = Title; }
	//implementation
	Mediatype getMediatype() override { return m_mediatype; }
	std::string& getTitle() override { return m_title; }
	status getStatus() override { return m_status; }
	//Title
	void changeTitle(std::string& newTitle) { m_title = newTitle; }
	//Status
	void changeStatus(status newstatus) { m_status = newstatus; }
	//Support
	void changeSupport(Film_Support newsupport) { m_support = newsupport; }
	Film_Support& getSupport() { return m_support; }
	//Restriction
	void changeAgeRestriction(int newrestriction) { m_agerestriction = newrestriction; }
	int& getAgeRestriction() { return m_agerestriction; }
private:
	Film_Support m_support;
	int m_agerestriction;
};
class VideoGame : public Media
{
public:
	VideoGame(std::string Title, game_Studio studio, int Pegi, game_gender gender) :m_studio(studio), m_pegi(Pegi), m_gender(gender) { m_mediatype = game;  m_title = Title; }
	//implementation
	Mediatype getMediatype() override { return m_mediatype; }
	std::string& getTitle() override { return m_title; }
	status getStatus() override { return m_status; }
	//Title
	void changeTitle(std::string& newTitle) { m_title = newTitle; }
	//Status
	void changeStatus(status newstatus) { m_status = newstatus; }
	//Studio
	void changeStudio(game_Studio newstudio) { m_studio = newstudio; }
	game_Studio& getStudio() { return m_studio; }
	//Pegi
	void changepegi(int newpegi) { m_pegi = newpegi; }
	int& getAgepegi() { return m_pegi; }
	//gender
	void changeGender(game_gender newgender) { m_gender = newgender; }
	game_gender& getGender() { return m_gender; }
private:
	game_Studio m_studio;
	int m_pegi;
	game_gender m_gender;
};
