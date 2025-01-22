
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
	Client(std::string name, std::string firstname, int age, std::string address, std::string phoneNumber);
	~Client()
	{
	}
	//implementation
	object_type gettype() override;
	//name
	void changename(std::string newname);
	std::string& getname();
	//firstname
	void changefirstname(std::string newfirstname);
	std::string& getfirstname();
	//age
	void changeage(int newage);
	int getage();
	//address
	void changeaddress(std::string newaddress);
	std::string& getaddress();
	//phoneNumber
	void changephoneNumber(std::string newphoneNumber);
	std::string& getphoneNumber();
	// rent media
	void addmedia(Media* media);
	void removemedia(Media* media);
	std::vector<Media*> getmediarent();
private:
	std::string m_name;
	std::string m_firstname;
	int m_age;
	std::string m_addressMail;
	std::string m_phoneNumber;
	std::vector<Media*> m_rent;

	/*std::vector<Media> m_emprund;*/
};
class Media :public Object
{
public:
	Media();
	//implementation
	object_type gettype() override;
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
	Book(std::string Title, std::string ISBN);
	//implementation
	Mediatype getMediatype() override;
	std::string& getTitle() override;
	status getStatus() override;
	//Title
	void changeTitle(std::string& newTitle);
	//Status
	void changeStatus(status newstatus);
	//ISBN
	void changeISBN(std::string& newTitle);
	std::string& getISBN();
private:
	std::string m_ISBN;
};
class Film : public Media
{
public:
	Film(std::string Title, Film_Support support, int agerestriction);
	//implementation
	Mediatype getMediatype() override;
	std::string& getTitle() override;
	status getStatus() override;
	//Title
	void changeTitle(std::string& newTitle);
	//Status
	void changeStatus(status newstatus);
	//Support
	void changeSupport(Film_Support newsupport);
	Film_Support& getSupport();
	//Restriction
	void changeAgeRestriction(int newrestriction);
	int& getAgeRestriction();
private:
	Film_Support m_support;
	int m_agerestriction;
};
class VideoGame : public Media
{
public:
	VideoGame(std::string Title, game_Studio studio, int Pegi, game_gender gender);
	//implementation
	Mediatype getMediatype() override;
	std::string& getTitle() override;
	status getStatus() override;

	void changeTitle(std::string& newTitle);
	//Title
	//Status
	void changeStatus(status newstatus);
	//Studio
	void changeStudio(game_Studio newstudio);
	game_Studio& getStudio();
	//Pegi
	void changepegi(int newpegi);
	int& getAgepegi();
	//gender
	void changeGender(game_gender newgender);
	game_gender& getGender();
private:
	game_Studio m_studio;
	int m_pegi;
	game_gender m_gender;
};
