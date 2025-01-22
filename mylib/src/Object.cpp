//#include "Object.h"
//
//Client::Client(std::string name, std::string firstname, int age, std::string address, std::string phoneNumber)
//	:m_name(name)
//	, m_firstname(firstname)
//	, m_age(age)
//	, m_addressMail(address)
//	, m_phoneNumber(phoneNumber)
//{
//	m_type = Client_type;
//}
//
////implementation
//
//object_type Client::gettype() { return m_type; }
//
////name
//
//void Client::changename(std::string newname) { m_name = newname; }
//
//std::string& Client::getname() { return m_name; }
//
////firstname
//
//void Client::changefirstname(std::string newfirstname) { m_firstname = newfirstname; }
//
//std::string& Client::getfirstname() { return m_firstname; }
//
////age
//
//void Client::changeage(int newage) { m_age = newage; }
//
//int Client::getage() { return m_age; }
//
////address
//
//void Client::changeaddress(std::string newaddress) { m_addressMail = newaddress; }
//
//std::string& Client::getaddress() { return m_addressMail; }
//
////phoneNumber
//
//void Client::changephoneNumber(std::string newphoneNumber) { m_phoneNumber = newphoneNumber; }
//
//std::string& Client::getphoneNumber() { return m_phoneNumber; }
//
//// rent media
//
//void Client::addmedia(Media* media) { m_rent.push_back(media); }
//
//void Client::removemedia(Media* media)
//{
//	for (auto it = m_rent.begin(); it != m_rent.end();)
//	{
//		if (*it == media)
//		{
//			it = m_rent.erase(it);
//			break;
//		}
//		else
//		{
//			++it;
//		}
//	}
//}
//
//std::vector<Media*> Client::getmediarent() { return m_rent; }
//
//Media::Media() { m_type = Media_type; m_status = available; }
//
////implementation
//
//object_type Media::gettype() { return m_type; }
//
//Book::Book(std::string Title, std::string ISBN) :m_ISBN(ISBN) { m_mediatype = book;  m_title = Title; }
//
////implementation
//
//
//Mediatype Book::getMediatype() { return m_mediatype; }
//
//std::string& Book::getTitle() { return m_title; }
//
//status Book::getStatus() { return m_status; }
//
////Title
//
//void Book::changeTitle(std::string& newTitle) { m_title = newTitle; }
//
////Status
//
//void Book::changeStatus(status newstatus) { m_status = newstatus; }
//
////ISBN
//
//void Book::changeISBN(std::string& newTitle) { m_ISBN = newTitle; }
//
//std::string& Book::getISBN() { return m_ISBN; }
//
//Film::Film(std::string Title, Film_Support support, int agerestriction) :m_support(support), m_agerestriction(agerestriction) { m_mediatype = film;  m_title = Title; }
//
////implementation
//
//Mediatype Film::getMediatype() { return m_mediatype; }
//
//std::string& Film::getTitle() { return m_title; }
//
//status Film::getStatus() { return m_status; }
//
////Title
//
//void Film::changeTitle(std::string& newTitle) { m_title = newTitle; }
//
////Status
//
// void Film::changeStatus(status newstatus) { m_status = newstatus; }
//
////Support
//
// void Film::changeSupport(Film_Support newsupport) { m_support = newsupport; }
//
// Film_Support& Film::getSupport() { return m_support; }
//
////Restriction
//
// void Film::changeAgeRestriction(int newrestriction) { m_agerestriction = newrestriction; }
//
// int& Film::getAgeRestriction() { return m_agerestriction; }
//
// VideoGame::VideoGame(std::string Title, game_Studio studio, int Pegi, game_gender gender) :m_studio(studio), m_pegi(Pegi), m_gender(gender) { m_mediatype = game;  m_title = Title; }
//
////implementation
//
// Mediatype VideoGame::getMediatype() { return m_mediatype; }
//
// std::string& VideoGame::getTitle() { return m_title; }
//
// status VideoGame::getStatus() { return m_status; }
//
// void VideoGame::changeTitle(std::string& newTitle) { m_title = newTitle; }
//
////Title
////Status
//
// void VideoGame::changeStatus(status newstatus) { m_status = newstatus; }
//
////Studio
//
// void VideoGame::changeStudio(game_Studio newstudio) { m_studio = newstudio; }
//
//game_Studio& VideoGame::getStudio() { return m_studio; }
//
////Pegi
//
//void VideoGame::changepegi(int newpegi) { m_pegi = newpegi; }
//
//int& VideoGame::getAgepegi() { return m_pegi; }
//
////gender
//
//void VideoGame::changeGender(game_gender newgender) { m_gender = newgender; }
//
// game_gender& VideoGame::getGender() { return m_gender; }
