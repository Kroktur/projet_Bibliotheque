//#pragma once
//#include "Object.h"
//// to remove
//#include <iostream>
//#include <vector>
//class mediatheque
//{
//public:
//	std::vector<Media*> showClientRent(const std::string& address);
//	void ReturnBook(const std::string& address, const std::string Tittle);
//	void ReturnFilm(const std::string& address, const std::string Tittle);
//	void ReturnVideoGame(const std::string& address, const std::string Tittle);
//	void rentBook(const std::string& address, const std::string Tittle);
//	void rentFilm(const std::string& address, const std::string Tittle);
//	void rentVideoGame(const std::string& address, const std::string Tittle);
//	void addBook(const std::string& Title, const std::string& ISBN);
//	void removeBook(std::vector<Media*> list);
//	void addFilm(const std::string& Title, const Film_Support& support, const int& agerestriction);
//	void removeFilm(std::vector<Media*> list);
//	void addVideogame(const std::string& Title, const game_Studio& studio, const int& Pegi, const game_gender& gender);
//	void removeVideoGame(std::vector<Media*> list);
//	//media 
//	void showdmedia(std::vector<Media*>list);
//	std::vector<Media*> Findmediabytitle(const std::string& title);
//	std::vector<Media*> Findmediabystatus(const status& statut);
//	std::vector<Media*> FindBook(std::vector<Media*> list);
//	std::vector<Media*> FindFilm(std::vector<Media*> list);
//	std::vector<Media*> FindVideoGame(std::vector<Media*> list);
//	// client
//	void addclient(const std::string& name, const std::string& firstname, const int& age, const std::string& address, const std::string& phoneNumber);
//	std::vector<Client*> Findclientsbyname(const std::string& name);
//	std::vector<Client*> Findclientsbyfirstname(const std::string& firstname);
//	std::vector<Client*> Findclientsbyage(const int& age);
//	std::vector<Client*> Findclientsbyaddress(const std::string& address);
//	std::vector<Client*> FindclientsbyphoneNumber(const std::string& phoneNumber);
//	void showclients(std::vector<Client*> list);
//	bool clientexists(const std::string& name, const std::string& firstname, const int& age, const std::string& address, const std::string& phoneNumber);
//	bool Bookalreadeyexist(const std::string& Title, const std::string& ISBN);
//	bool Filmalreadeyexist(const std::string& Title, const Film_Support& support, const int& agerestriction);
//	bool VideoGamealreadeyexist(const std::string& Title, const game_Studio& studio, const int& Pegi, const game_gender& gender);
//
//	void deleteclient(const std::vector<Client*> list);
//	std::vector<Client*> getallclient();
//	std::vector<Media*> getallmedia();
//	std::vector<Media*> createcombinemedialist(std::vector<Media*> liste1 , std::vector<Media*> liste2);
//	std::vector<Client*> createcombineclientlist(std::vector<Client*> liste1, std::vector<Client*> liste2);
//	~mediatheque();
//private:
//	void showclient(Client* client);
//	void showBook(Media* media);
//	void showFilm(Media* media);
//	void showGame(Media* media);
//	bool clientbind(Client* client1, Client* client2);
//	bool Bookbind(Media* media, Media* media2);
//	bool Filmbind(Media* media, Media* media2);
//	bool VideoGamebind(Media* media, Media* media2);
//	void rentmedia(Client* client, std::vector<Media*> list);
//	//vecteur de client
//	std::vector<Client*> m_client;
//	//vecteur de mediat
//	std::vector<Media*> m_media;
//}; 
//class bibliothecaire
//{
//public:
//	bibliothecaire(mediatheque* Mediatheque);
//	void showClientRent(const std::string& address);
//	void ReturnBook(const std::string& address, const std::string& Tittle);
//	void ReturnFilm(const std::string& address, const std::string& Tittle);
//	void ReturnVideoGame(const std::string& address, const std::string& Tittle);
//	void rentBook(const std::string& address, const std::string& Tittle);
//	void rentFilm(const std::string& address, const std::string Tittle);
//	void rentVideoGame(const std::string& address, const std::string Tittle);
//	//add
//	void CreateClientAccount(const std::string& name, const std::string& firstname, const int& age, const std::string& address, const std::string& phoneNumber);
//	//show
//	void showclientbyname(const std::string& name);
//	void showclientbyfirstname(const std::string& firstname);
//	void showclientbyage(const int& age);
//	void showclientbyaddress(const std::string& address);
//	void showclientbyphoneNumber(const std::string& phoneNumber);
//	void showallclient();
//	//remove
//	void removebyname(const std::string& name);
//	void removebyfirstname(const std::string& firstname);
//	void removebyage(const int& age);
//	void removebyaddress(const std::string& address);
//	void removebyphoneNumber(const std::string& phoneNumber);
//	//media 
//	//add
//	void createBook(const std::string& Title, const std::string& ISBN);
//	void createFilm(const std::string& Title, const Film_Support& support, const int& agerestriction);
//	void createVideoGame(const std::string& Title, const game_Studio& studio, const int& Pegi, const game_gender& gender);
//	//remove
//	void removeBookbytitle(const std::string& title);
//	void removeFilmbytitle(const std::string& title);
//	void removeVideoGamebytitle(const std::string& title);
//	//find
//	void Findbystatus(const std::string& statut);
//	void findbyname(const std::string& name);
//	void findbytype(const std::string& type);
//	//show
//	void showallmedia();
//	~bibliothecaire();
//
//private:
//	bool Clientalereadyexist(const std::string& name, const std::string& firstname, const int& age, const std::string& address, const std::string& phoneNumber);
//	bool Bookalreadeyexist(const std::string& Title, const std::string& ISBN);
//	bool Filmalreadeyexist(const std::string& Title, const Film_Support& support, const int& agerestriction);
//	bool VideoGamealreadeyexist(const std::string& Title, const game_Studio& studio, const int& Pegi, const game_gender& gender);
//
//	mediatheque* m_mediatheque;
//};