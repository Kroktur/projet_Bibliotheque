#pragma once
#include "Object.h"
// to remove
#include <iostream>
#include <vector>
class mediatheque
{
public:
	void addBook(const std::string& Title, const std::string& ISBN)
	{
		m_media.push_back(new Book{ Title ,ISBN });
	}
	void removeBook(std::vector<Media*> list)
	{
		for (auto it = m_media.begin(); it != m_media.end(); )
		{
			bool found = false;
			for (auto bookToDelete : list)
			{
				if (Bookbind(*it, bookToDelete))
				{
					found = true;
					break;
				}
			}
			if (found)
			{
				delete* it;
				it = m_media.erase(it);
			}
			else
				++it;
		}
	}
	void addFilm(const std::string& Title, const Film_Support& support, const int& agerestriction)
	{
		m_media.push_back(new Film{ Title ,support ,agerestriction });
	}
	void removeFilm(std::vector<Media*> list)
	{
		for (auto it = m_media.begin(); it != m_media.end(); )
		{
			bool found = false;
			for (auto filmToDelete : list)
			{
				if (Filmbind(*it, filmToDelete))
				{
					found = true;
					break;
				}
			}
			if (found)
			{
				delete* it;
				it = m_media.erase(it);
			}
			else
				++it;
		}
	}
	void addVideogame(const std::string& Title, const game_Studio& studio, const int& Pegi, const game_gender& gender)
	{
		m_media.push_back(new VideoGame{ Title ,studio ,Pegi ,gender });
	}
	void removeVideoGame(std::vector<Media*> list)
	{
		for (auto it = m_media.begin(); it != m_media.end(); )
		{
			bool found = false;
			for (auto videogameToDelete : list)
			{
				if (VideoGamebind(*it, videogameToDelete))
				{
					found = true;
					break;
				}
			}
			if (found)
			{
				delete* it;
				it = m_media.erase(it);
			}
			else
				++it;
		}
	}
	//media 
	void showdmedia(std::vector<Media*>list)
	{
		for (auto i = 0; i < list.size(); ++i)
		{
			if (list[i]->getMediatype() == book)
			{
				showBook(list[i]);
			}
			if (list[i]->getMediatype() == film)
			{
				showFilm(list[i]);
			}
			if (list[i]->getMediatype() == game)
			{
				showGame(list[i]);
			}
		}

	}
	std::vector<Media*> Findmediabytitle(const std::string& title)
	{
		std::vector<Media*> tmplist;
		for (auto& client : m_media)
		{
			if (client->getTitle() == title)
				tmplist.push_back(client);
		}
		return tmplist;
	}
	std::vector<Media*> Findmediabystatus(const status& statut)
	{
		std::vector<Media*> tmplist;
		for (auto& client : m_media)
		{
			if (client->getStatus() == statut)
				tmplist.push_back(client);
		}
		return tmplist;
	}
	std::vector<Media*> FindBook(std::vector<Media*> list)
	{
		std::vector<Media*> tmplist;
		for (auto& media : list)
		{
			if (media->getMediatype() == book)
			tmplist.push_back(static_cast<Media*>(media));
		}
		return tmplist;
	}
	std::vector<Media*> FindFilm(std::vector<Media*> list)
	{
		std::vector<Media*> tmplist;
		for (auto& media : list)
		{
			if (media->getMediatype() == film)
			tmplist.push_back(static_cast<Media*>(media));
		}
		return tmplist;
	}
	std::vector<Media*> FindVideoGame(std::vector<Media*> list)
	{
		std::vector<Media*> tmplist;
		for (auto& media : list)
		{
			if (media->getMediatype() == game)
			tmplist.push_back(static_cast<Media*>(media));
		}
		return tmplist;
	}
	// client
	void addclient(const std::string& name, const std::string& firstname, const int& age, const std::string& address, const std::string& phoneNumber)
	{
		m_client.push_back(new Client{ name ,firstname,age,address, phoneNumber });

	}
	std::vector<Client*> Findclientsbyname(const std::string& name)
	{
		std::vector<Client*> tmplist;
		for (auto& client : m_client)
		{
			if (client->getname() == name)
				tmplist.push_back(client);
		}
		return tmplist;
	}
	std::vector<Client*> Findclientsbyfirstname(const std::string& firstname)
	{
		std::vector<Client*> tmplist;
		for (auto& client : m_client)
		{
			if (client->getfirstname() == firstname)
				tmplist.push_back(client);
		}
		return tmplist;
	}
	std::vector<Client*> Findclientsbyage(const int& age)
	{
		std::vector<Client*> tmplist;
		for (auto& client : m_client)
		{
			if (client->getage() == age)
				tmplist.push_back(client);
		}
		return tmplist;
	}
	std::vector<Client*> Findclientsbyaddress(const std::string& address)
	{
		std::vector<Client*> tmplist;
		for (auto& client : m_client)
		{
			if (client->getaddress() == address)
				tmplist.push_back(client);
		}
		return tmplist;
	}
	std::vector<Client*> FindclientsbyphoneNumber(const std::string& phoneNumber)
	{
		std::vector<Client*> tmplist;
		for (auto& client : m_client)
		{
			if (client->getphoneNumber() == phoneNumber)
				tmplist.push_back(client);
		}
		return tmplist;
	}
	void showclients(std::vector<Client*> list)
	{
		for (auto i = 0; i < list.size(); ++i)
			showclient(list[i]);
	}
	bool clientexists(const std::string& name, const std::string& firstname, const int& age, const std::string& address, const std::string& phoneNumber)
	{
		for (auto& client : m_client)
		{
			if (client->getname() == name && client->getfirstname() == firstname && client->getage() == age && client->getaddress() == address && client->getphoneNumber() == phoneNumber)
				return true;
		}
		return false;
	}
	bool Bookalreadeyexist(const std::string& Title, const std::string& ISBN)
	{
		Book* mybook = new Book{ Title ,ISBN };
		for (auto& book : m_media)
		{

			if (Bookbind(book, mybook))
			{
				delete mybook;
				return true;
			}
		}
		delete mybook;
		return false;
	}
	bool Filmalreadeyexist(const std::string& Title, const Film_Support& support, const int& agerestriction)
	{
		Film* myfilm = new Film{ Title ,support,agerestriction };
		for (auto& book : m_media)
		{

			if (Filmbind(book, myfilm))
			{
				delete myfilm;
				return true;
			}
		}
		delete myfilm;
		return false;
	}
	bool VideoGamealreadeyexist(const std::string& Title, const game_Studio& studio, const int& Pegi, const game_gender& gender)
	{
		VideoGame* mygame = new VideoGame{ Title ,studio,Pegi,gender };
		for (auto& book : m_media)
		{

			if (VideoGamebind(book, mygame))
			{
				delete mygame;
				return true;
			}
		}
		delete mygame;
		return false;
	}

	void deleteclient(const std::vector<Client*> list)
	{
		for (auto it = m_client.begin(); it != m_client.end(); )
		{
			bool found = false;
			for (auto clientToDelete : list)
			{
				if (clientbind(*it, clientToDelete))
				{
					found = true;
					break;
				}
			}
			if (found)
			{
				delete* it;
				it = m_client.erase(it);
			}
			else
				++it;
		}
	}
	std::vector<Client*> getallclient()
	{
		std::vector<Client*> tmplist;
		for (auto& client : m_client)
		{
			tmplist.push_back(client);
		}
		return tmplist;
	}
	std::vector<Media*> getallmedia()
	{
		std::vector<Media*>tmplist;
		for (auto& media : m_media)
		{
			tmplist.push_back(media);
		}
		return tmplist;
	}
	std::vector<Media*> createcombinemedialist(std::vector<Media*> liste1 , std::vector<Media*> liste2)
	{
		std::vector<Media*>tmplist;
		for (auto& lise1idx : liste1)
		{
			for (auto& list2idx : liste2)
			{
				if (Bookbind(lise1idx, list2idx) || Filmbind(lise1idx, list2idx) || VideoGamebind(lise1idx, list2idx))
					tmplist.push_back(lise1idx);
			}
		}
		return tmplist;
	}
	std::vector<Client*> createcombineclientlist(std::vector<Client*> liste1, std::vector<Client*> liste2)
	{
		std::vector<Client*>tmplist;
		for (auto& lise1idx : liste1)
		{
			for (auto& list2idx : liste2)
			{
				if (clientbind(lise1idx, list2idx))
					tmplist.push_back(lise1idx);
			}
		}
		return tmplist;
	}

private:
	void showclient(Client* client)
	{
		// add show class 
		//exemple
		std::cout << client->getname() << std::endl;
		std::cout << client->getfirstname() << std::endl;
		std::cout << client->getage() << std::endl;
		std::cout << client->getaddress() << std::endl;
		std::cout << client->getphoneNumber() << std::endl;
		//
	}
	void showBook(Media* media)
	{
		auto mymedia = static_cast<Book*>(media);
		// add show class 
		//exemple
		std::cout << mymedia->getTitle() << std::endl;
		std::cout << mymedia->getISBN() << std::endl;
		//
	}
	void showFilm(Media* media)
	{
		auto mymedia = static_cast<Film*>(media);
		// add show class 
		//exemple
		std::cout << mymedia->getTitle() << std::endl;
		std::cout << mymedia->getAgeRestriction() << std::endl;
		std::cout << mymedia->getSupport() << std::endl;
		//
	}
	void showGame(Media* media)
	{
		auto mymedia = static_cast<VideoGame*>(media);
		// add show class 
		//exemple
		std::cout << mymedia->getTitle() << std::endl;
		std::cout << mymedia->getAgepegi() << std::endl;
		std::cout << mymedia->getGender() << std::endl;
		std::cout << mymedia->getStudio() << std::endl;
		//
	}
	bool clientbind(Client* client1, Client* client2)
	{
		if (client1->getname() == client2->getname()
			&& client1->getfirstname() == client2->getfirstname()
			&& client1->getage() == client2->getage()
			&& client1->getaddress() == client2->getaddress()
			&& client1->getphoneNumber() == client2->getphoneNumber())
			return true;
		else
			return false;

	}
	bool Bookbind(Media* media, Media* media2)
	{
		if (media->getMediatype() != book || media2->getMediatype() != book)
			return false;
		Book* book1 = static_cast<Book*>(media);
		Book* book2 = static_cast<Book*>(media2);
		if (book1->getTitle() == book2->getTitle()
			&& book1->getISBN() == book2->getISBN())
			return true;
		else
			return false;
	}
	bool Filmbind(Media* media, Media* media2)
	{
		if (media->getMediatype() != film || media2->getMediatype() != film)
			return false;
		Film* film1 = static_cast<Film*>(media);
		Film* film2 = static_cast<Film*>(media2);
		if (film1->getTitle() == film2->getTitle()
			&& film1->getAgeRestriction() == film2->getAgeRestriction()
			&& film1->getSupport() == film2->getSupport()
			)
			return true;
		else
			return false;
	}
	bool VideoGamebind(Media* media, Media* media2)
	{
		if (media->getMediatype() != game || media2->getMediatype() != game)
			return false;
		VideoGame* game1 = static_cast<VideoGame*>(media);
		VideoGame* game2 = static_cast<VideoGame*>(media2);
		if (game1->getTitle() == game2->getTitle()
			&& game1->getAgepegi() == game2->getAgepegi()
			&& game1->getGender() == game2->getGender()
			&& game1->getStudio() == game2->getStudio()
			)
			return true;
		else
			return false;
	}
	void rentmedia(Client* client, std::vector<Media*> list)
	{
		for (auto& listidx : list)
		{
			client->addmedia(listidx);
		}
	}
	//vecteur de client
	std::vector<Client*> m_client;
	//vecteur de mediat
	std::vector<Media*> m_media;
}; 
class bibliothecaire
{
public:
	bibliothecaire(mediatheque* Mediatheque) : m_mediatheque(Mediatheque) {}
	//add
	void CreateClientAccount(const std::string& name, const std::string& firstname, const int& age, const std::string& address, const std::string& phoneNumber)
	{
		if (!Clientalereadyexist(name, firstname, age, address, phoneNumber))
			m_mediatheque->addclient(name, firstname, age, address, phoneNumber);
	}
	//show
	void showclientbyname(const std::string& name)
	{
		auto myclientlist = m_mediatheque->Findclientsbyname(name);
		m_mediatheque->showclients(myclientlist);
	}
	void showclientbyfirstname(const std::string& firstname)
	{
		auto myclientlist = m_mediatheque->Findclientsbyfirstname(firstname);
		m_mediatheque->showclients(myclientlist);
	}
	void showclientbyage(const int& age)
	{
		auto myclientlist = m_mediatheque->Findclientsbyage(age);
		m_mediatheque->showclients(myclientlist);
	}
	void showclientbyaddress(const std::string& address)
	{
		auto myclientlist = m_mediatheque->Findclientsbyaddress(address);
		m_mediatheque->showclients(myclientlist);
	}
	void showclientbyphoneNumber(const std::string& phoneNumber)
	{
		auto myclientlist = m_mediatheque->FindclientsbyphoneNumber(phoneNumber);
		m_mediatheque->showclients(myclientlist);
	}
	void showallclient()
	{
		auto myclientlist = m_mediatheque->getallclient();
		m_mediatheque->showclients(myclientlist);
	}
	//remove
	void removebyname(const std::string& name)
	{
		auto myclientlist = m_mediatheque->Findclientsbyname(name);
		m_mediatheque->deleteclient(myclientlist);
	}
	void removebyfirstname(const std::string& firstname)
	{
		auto myclientlist = m_mediatheque->Findclientsbyfirstname(firstname);
		m_mediatheque->deleteclient(myclientlist);
	}
	void removebyage(const int& age)
	{
		auto myclientlist = m_mediatheque->Findclientsbyage(age);
		m_mediatheque->deleteclient(myclientlist);
	}
	void removebyaddress(const std::string& address)
	{
		auto myclientlist = m_mediatheque->Findclientsbyaddress(address);
		m_mediatheque->deleteclient(myclientlist);
	}
	void removebyphoneNumber(const std::string& phoneNumber)
	{
		auto myclientlist = m_mediatheque->FindclientsbyphoneNumber(phoneNumber);
		m_mediatheque->deleteclient(myclientlist);
	}
	//media 
	//add
	void createBook(const std::string& Title, const std::string& ISBN)
	{
		if (!Bookalreadeyexist(Title, ISBN))
			m_mediatheque->addBook(Title, ISBN);
	}
	void createFilm(const std::string& Title, const Film_Support& support, const int& agerestriction)
	{
		if (!Filmalreadeyexist(Title, support, agerestriction))
			m_mediatheque->addFilm(Title, support, agerestriction);
	}
	void createVideoGame(const std::string& Title, const game_Studio& studio, const int& Pegi, const game_gender& gender)
	{
		if (!VideoGamealreadeyexist(Title, studio, Pegi, gender))
			m_mediatheque->addVideogame(Title, studio, Pegi, gender);
	}
	//remove
	void removeBookbytitle(const std::string& title)
	{
		m_mediatheque->removeBook(m_mediatheque->FindBook(m_mediatheque->Findmediabytitle(title)));
	}
	void removeFilmbytitle(const std::string& title)
	{
		m_mediatheque->removeFilm(m_mediatheque->FindFilm(m_mediatheque->Findmediabytitle(title)));
	}
	void removeVideoGamebytitle(const std::string& title)
	{
		m_mediatheque->removeVideoGame(m_mediatheque->FindVideoGame(m_mediatheque->Findmediabytitle(title)));
	}
	//find
	void Findbystatus(const std::string& statut)
	{
		if (statut == "available")
			m_mediatheque->showdmedia(m_mediatheque->Findmediabystatus(available));
		if (statut == "borrowed")
			m_mediatheque->showdmedia(m_mediatheque->Findmediabystatus(borrowed));
	}
	void findbyname(const std::string& name)
	{
		m_mediatheque->showdmedia(m_mediatheque->Findmediabytitle(name));
	}
	void findbytype(const std::string& type)
	{
		if (type == "Book")
			m_mediatheque->showdmedia(m_mediatheque->FindBook(m_mediatheque->getallmedia()));
		if (type == "Film")
			m_mediatheque->showdmedia(m_mediatheque->FindFilm(m_mediatheque->getallmedia()));
		if (type == "VideoGame")
			m_mediatheque->showdmedia(m_mediatheque->FindVideoGame(m_mediatheque->getallmedia()));
	}
	//show
	void showallmedia()
	{
		m_mediatheque->showdmedia(m_mediatheque->getallmedia());
	}


private:
	bool Clientalereadyexist(const std::string& name, const std::string& firstname, const int& age, const std::string& address, const std::string& phoneNumber)
	{
		return m_mediatheque->clientexists(name, firstname, age, address, phoneNumber);
	}
	bool Bookalreadeyexist(const std::string& Title, const std::string& ISBN)
	{
		return m_mediatheque->Bookalreadeyexist(Title, ISBN);
	}
	bool Filmalreadeyexist(const std::string& Title, const Film_Support& support, const int& agerestriction)
	{
		return m_mediatheque->Filmalreadeyexist(Title, support, agerestriction);
	}
	bool VideoGamealreadeyexist(const std::string& Title, const game_Studio& studio, const int& Pegi, const game_gender& gender)
	{
		return m_mediatheque->VideoGamealreadeyexist(Title, studio, Pegi, gender);
	}

	mediatheque* m_mediatheque;
};