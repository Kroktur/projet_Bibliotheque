#include "mediatheque.h"

std::vector<Media*> mediatheque::showClientRent(const std::string& address)
{
	std::vector<Media*> tmplist;
	if (Findclientsbyaddress(address).size() != 1)
		return tmplist;
	tmplist = Findclientsbyaddress(address).front()->getmediarent();
	return tmplist;
}

void mediatheque::ReturnBook(const std::string& address, const std::string Tittle)
{
	std::vector<Media*> tmplist;
	if (Findclientsbyaddress(address).size() != 1)
		return;
	tmplist = Findclientsbyaddress(address).front()->getmediarent();
	for (auto& listidx : tmplist)
	{
		if (listidx->getMediatype() != book)
			continue;
		if (static_cast<Book*>(listidx)->getTitle() != Tittle)
			continue;
		static_cast<Book*>(listidx)->changeStatus(available);
		Findclientsbyaddress(address).front()->removemedia(listidx);

	}
}

void mediatheque::ReturnFilm(const std::string& address, const std::string Tittle)
{
	std::vector<Media*> tmplist;
	if (Findclientsbyaddress(address).size() != 1)
		return;
	tmplist = Findclientsbyaddress(address).front()->getmediarent();
	for (auto& listidx : tmplist)
	{
		if (listidx->getMediatype() != film)
			continue;
		if (static_cast<Film*>(listidx)->getTitle() != Tittle)
			continue;
		static_cast<Film*>(listidx)->changeStatus(available);
		Findclientsbyaddress(address).front()->removemedia(listidx);

	}
}

void mediatheque::ReturnVideoGame(const std::string& address, const std::string Tittle)
{
	std::vector<Media*> tmplist;
	if (Findclientsbyaddress(address).size() != 1)
		return;
	tmplist = Findclientsbyaddress(address).front()->getmediarent();
	for (auto& listidx : tmplist)
	{
		if (listidx->getMediatype() != game)
			continue;
		if (static_cast<VideoGame*>(listidx)->getTitle() != Tittle)
			continue;
		static_cast<VideoGame*>(listidx)->changeStatus(available);
		Findclientsbyaddress(address).front()->removemedia(listidx);

	}
}

void mediatheque::rentBook(const std::string& address, const std::string Tittle)
{
	std::vector<Media*> tmplist;
	std::vector<Media*> tmplistsort;
	if (Findclientsbyaddress(address).size() != 1)
		return;
	tmplist = FindBook(Findmediabytitle((Tittle)));
	for (auto& listidx : tmplist)
	{
		if (static_cast<Book*>(listidx)->getStatus() == available)
		{
			static_cast<Book*>(listidx)->changeStatus(borrowed);
			tmplistsort.push_back(listidx);
		}
	}
	rentmedia(Findclientsbyaddress(address).front(), tmplistsort);
}

void mediatheque::rentFilm(const std::string& address, const std::string Tittle)
{
	std::vector<Media*> tmplist;
	std::vector<Media*> tmplistsort;
	if (Findclientsbyaddress(address).size() != 1)
		return;
	tmplist = FindFilm(Findmediabytitle((Tittle)));
	for (auto& listidx : tmplist)
	{
		if (static_cast<Film*>(listidx)->getAgeRestriction() <= Findclientsbyaddress(address).front()->getage() && static_cast<Film*>(listidx)->getStatus() == available)
		{
			static_cast<Film*>(listidx)->changeStatus(borrowed);
			tmplistsort.push_back(listidx);
		}

	}
	rentmedia(Findclientsbyaddress(address).front(), tmplistsort);
}

void mediatheque::rentVideoGame(const std::string& address, const std::string Tittle)
{
	std::vector<Media*> tmplist;
	std::vector<Media*> tmplistsort;
	if (Findclientsbyaddress(address).size() != 1)
		return;
	tmplist = FindVideoGame(Findmediabytitle((Tittle)));
	for (auto& listidx : tmplist)
	{
		if (static_cast<VideoGame*>(listidx)->getAgepegi() <= Findclientsbyaddress(address).front()->getage() && static_cast<VideoGame*>(listidx)->getStatus() == available)
		{
			static_cast<VideoGame*>(listidx)->changeStatus(borrowed);
			tmplistsort.push_back(listidx);
		}
	}
	rentmedia(Findclientsbyaddress(address).front(), tmplistsort);
}

void mediatheque::addBook(const std::string& Title, const std::string& ISBN)
{
	m_media.push_back(new Book{ Title ,ISBN });
}

void mediatheque::removeBook(std::vector<Media*> list)
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

void mediatheque::addFilm(const std::string& Title, const Film_Support& support, const int& agerestriction)
{
	m_media.push_back(new Film{ Title ,support ,agerestriction });
}

void mediatheque::removeFilm(std::vector<Media*> list)
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

void mediatheque::addVideogame(const std::string& Title, const game_Studio& studio, const int& Pegi, const game_gender& gender)
{
	m_media.push_back(new VideoGame{ Title ,studio ,Pegi ,gender });
}

void mediatheque::removeVideoGame(std::vector<Media*> list)
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

void mediatheque::showdmedia(std::vector<Media*> list)
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

std::vector<Media*> mediatheque::Findmediabytitle(const std::string& title)
{
	std::vector<Media*> tmplist;
	for (auto& client : m_media)
	{
		if (client->getTitle() == title)
			tmplist.push_back(client);
	}
	return tmplist;
}

std::vector<Media*> mediatheque::Findmediabystatus(const status& statut)
{
	std::vector<Media*> tmplist;
	for (auto& client : m_media)
	{
		if (client->getStatus() == statut)
			tmplist.push_back(client);
	}
	return tmplist;
}

std::vector<Media*> mediatheque::FindBook(std::vector<Media*> list)
{
	std::vector<Media*> tmplist;
	for (auto& media : list)
	{
		if (media->getMediatype() == book)
			tmplist.push_back(static_cast<Media*>(media));
	}
	return tmplist;
}

std::vector<Media*> mediatheque::FindFilm(std::vector<Media*> list)
{
	std::vector<Media*> tmplist;
	for (auto& media : list)
	{
		if (media->getMediatype() == film)
			tmplist.push_back(static_cast<Media*>(media));
	}
	return tmplist;
}

std::vector<Media*> mediatheque::FindVideoGame(std::vector<Media*> list)
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

void mediatheque::addclient(const std::string& name, const std::string& firstname, const int& age, const std::string& address, const std::string& phoneNumber)
{
	m_client.push_back(new Client{ name ,firstname,age,address, phoneNumber });

}

std::vector<Client*> mediatheque::Findclientsbyname(const std::string& name)
{
	std::vector<Client*> tmplist;
	for (auto& client : m_client)
	{
		if (client->getname() == name)
			tmplist.push_back(client);
	}
	return tmplist;
}

std::vector<Client*> mediatheque::Findclientsbyfirstname(const std::string& firstname)
{
	std::vector<Client*> tmplist;
	for (auto& client : m_client)
	{
		if (client->getfirstname() == firstname)
			tmplist.push_back(client);
	}
	return tmplist;
}

std::vector<Client*> mediatheque::Findclientsbyage(const int& age)
{
	std::vector<Client*> tmplist;
	for (auto& client : m_client)
	{
		if (client->getage() == age)
			tmplist.push_back(client);
	}
	return tmplist;
}

std::vector<Client*> mediatheque::Findclientsbyaddress(const std::string& address)
{
	std::vector<Client*> tmplist;
	for (auto& client : m_client)
	{
		if (client->getaddress() == address)
			tmplist.push_back(client);
	}
	return tmplist;
}

std::vector<Client*> mediatheque::FindclientsbyphoneNumber(const std::string& phoneNumber)
{
	std::vector<Client*> tmplist;
	for (auto& client : m_client)
	{
		if (client->getphoneNumber() == phoneNumber)
			tmplist.push_back(client);
	}
	return tmplist;
}

void mediatheque::showclients(std::vector<Client*> list)
{
	for (auto i = 0; i < list.size(); ++i)
		showclient(list[i]);
}

bool mediatheque::clientexists(const std::string& name, const std::string& firstname, const int& age, const std::string& address, const std::string& phoneNumber)
{
	Client* myclient = new Client{ name ,firstname ,age ,address ,phoneNumber };
	for (auto& client : m_client)
	{
		if (clientbind(client, myclient))
		{
			delete myclient;
			return true;
		}
	}
	delete myclient;
	return false;
}

bool mediatheque::Bookalreadeyexist(const std::string& Title, const std::string& ISBN)
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

bool mediatheque::Filmalreadeyexist(const std::string& Title, const Film_Support& support, const int& agerestriction)
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

bool mediatheque::VideoGamealreadeyexist(const std::string& Title, const game_Studio& studio, const int& Pegi, const game_gender& gender)
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

void mediatheque::deleteclient(const std::vector<Client*> list)
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

std::vector<Client*> mediatheque::getallclient()
{
	std::vector<Client*> tmplist;
	for (auto& client : m_client)
	{
		tmplist.push_back(client);
	}
	return tmplist;
}

std::vector<Media*> mediatheque::getallmedia()
{
	std::vector<Media*>tmplist;
	for (auto& media : m_media)
	{
		tmplist.push_back(media);
	}
	return tmplist;
}

std::vector<Media*> mediatheque::createcombinemedialist(std::vector<Media*> liste1, std::vector<Media*> liste2)
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

std::vector<Client*> mediatheque::createcombineclientlist(std::vector<Client*> liste1, std::vector<Client*> liste2)
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

mediatheque::~mediatheque()
{
	for (auto& client : m_client)
	{
		delete client;
		client = nullptr;
	}
	for (auto& media : m_media)
	{
		delete media;
		media = nullptr;
	}
}

void mediatheque::showclient(Client* client)
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

void mediatheque::showBook(Media* media)
{
	auto mymedia = static_cast<Book*>(media);
	// add show class 
	//exemple
	std::cout << mymedia->getTitle() << std::endl;
	std::cout << mymedia->getISBN() << std::endl;
	//
}

void mediatheque::showFilm(Media* media)
{
	auto mymedia = static_cast<Film*>(media);
	// add show class 
	//exemple
	std::cout << mymedia->getTitle() << std::endl;
	std::cout << mymedia->getAgeRestriction() << std::endl;
	std::cout << mymedia->getSupport() << std::endl;
	//
}

void mediatheque::showGame(Media* media)
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

bool mediatheque::clientbind(Client* client1, Client* client2)
{
	if (client1->getaddress() == client2->getaddress()
		&& client1->getphoneNumber() == client2->getphoneNumber())
		return true;
	else
		return false;

}

bool mediatheque::Bookbind(Media* media, Media* media2)
{
	if (media->getMediatype() != book || media2->getMediatype() != book)
		return false;
	Book* book1 = static_cast<Book*>(media);
	Book* book2 = static_cast<Book*>(media2);
	if (book1->getISBN() == book2->getISBN())
		return true;
	else
		return false;
}

bool mediatheque::Filmbind(Media* media, Media* media2)
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

bool mediatheque::VideoGamebind(Media* media, Media* media2)
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

void mediatheque::rentmedia(Client* client, std::vector<Media*> list)
{
	for (auto& listidx : list)
	{
		client->addmedia(listidx);
	}
}

bibliothecaire::bibliothecaire(mediatheque* Mediatheque) : m_mediatheque(Mediatheque) {}

void bibliothecaire::showClientRent(const std::string& address)
{
	auto myclientlist = m_mediatheque->showClientRent(address);
	m_mediatheque->showdmedia(myclientlist);
}

void bibliothecaire::ReturnBook(const std::string& address, const std::string& Tittle)
{
	m_mediatheque->ReturnBook(address, Tittle);
}

void bibliothecaire::ReturnFilm(const std::string& address, const std::string& Tittle)
{
	m_mediatheque->ReturnFilm(address, Tittle);
}

void bibliothecaire::ReturnVideoGame(const std::string& address, const std::string& Tittle)
{
	m_mediatheque->ReturnVideoGame(address, Tittle);
}

void bibliothecaire::rentBook(const std::string& address, const std::string& Tittle)
{
	m_mediatheque->rentBook(address, Tittle);
}

void bibliothecaire::rentFilm(const std::string& address, const std::string Tittle)
{
	m_mediatheque->rentFilm(address, Tittle);
}

void bibliothecaire::rentVideoGame(const std::string& address, const std::string Tittle)
{
	m_mediatheque->rentVideoGame(address, Tittle);
}

//add

void bibliothecaire::CreateClientAccount(const std::string& name, const std::string& firstname, const int& age, const std::string& address, const std::string& phoneNumber)
{
	if (!Clientalereadyexist(name, firstname, age, address, phoneNumber))
		m_mediatheque->addclient(name, firstname, age, address, phoneNumber);
}

//show

void bibliothecaire::showclientbyname(const std::string& name)
{
	auto myclientlist = m_mediatheque->Findclientsbyname(name);
	m_mediatheque->showclients(myclientlist);
}

void bibliothecaire::showclientbyfirstname(const std::string& firstname)
{
	auto myclientlist = m_mediatheque->Findclientsbyfirstname(firstname);
	m_mediatheque->showclients(myclientlist);
}

void bibliothecaire::showclientbyage(const int& age)
{
	auto myclientlist = m_mediatheque->Findclientsbyage(age);
	m_mediatheque->showclients(myclientlist);
}

void bibliothecaire::showclientbyaddress(const std::string& address)
{
	auto myclientlist = m_mediatheque->Findclientsbyaddress(address);
	m_mediatheque->showclients(myclientlist);
}

void bibliothecaire::showclientbyphoneNumber(const std::string& phoneNumber)
{
	auto myclientlist = m_mediatheque->FindclientsbyphoneNumber(phoneNumber);
	m_mediatheque->showclients(myclientlist);
}

void bibliothecaire::showallclient()
{
	auto myclientlist = m_mediatheque->getallclient();
	m_mediatheque->showclients(myclientlist);
}

//remove

void bibliothecaire::removebyname(const std::string& name)
{
	auto myclientlist = m_mediatheque->Findclientsbyname(name);
	m_mediatheque->deleteclient(myclientlist);
}

void bibliothecaire::removebyfirstname(const std::string& firstname)
{
	auto myclientlist = m_mediatheque->Findclientsbyfirstname(firstname);
	m_mediatheque->deleteclient(myclientlist);
}

void bibliothecaire::removebyage(const int& age)
{
	auto myclientlist = m_mediatheque->Findclientsbyage(age);
	m_mediatheque->deleteclient(myclientlist);
}

void bibliothecaire::removebyaddress(const std::string& address)
{
	auto myclientlist = m_mediatheque->Findclientsbyaddress(address);
	m_mediatheque->deleteclient(myclientlist);
}

void bibliothecaire::removebyphoneNumber(const std::string& phoneNumber)
{
	auto myclientlist = m_mediatheque->FindclientsbyphoneNumber(phoneNumber);
	m_mediatheque->deleteclient(myclientlist);
}

//media 
//add

void bibliothecaire::createBook(const std::string& Title, const std::string& ISBN)
{
	if (!Bookalreadeyexist(Title, ISBN))
		m_mediatheque->addBook(Title, ISBN);
}

void bibliothecaire::createFilm(const std::string& Title, const Film_Support& support, const int& agerestriction)
{
	if (!Filmalreadeyexist(Title, support, agerestriction))
		m_mediatheque->addFilm(Title, support, agerestriction);
}

void bibliothecaire::createVideoGame(const std::string& Title, const game_Studio& studio, const int& Pegi, const game_gender& gender)
{
	if (!VideoGamealreadeyexist(Title, studio, Pegi, gender))
		m_mediatheque->addVideogame(Title, studio, Pegi, gender);
}

//remove

void bibliothecaire::removeBookbytitle(const std::string& title)
{
	m_mediatheque->removeBook(m_mediatheque->FindBook(m_mediatheque->Findmediabytitle(title)));
}

void bibliothecaire::removeFilmbytitle(const std::string& title)
{
	m_mediatheque->removeFilm(m_mediatheque->FindFilm(m_mediatheque->Findmediabytitle(title)));
}

void bibliothecaire::removeVideoGamebytitle(const std::string& title)
{
	m_mediatheque->removeVideoGame(m_mediatheque->FindVideoGame(m_mediatheque->Findmediabytitle(title)));
}

//find

void bibliothecaire::Findbystatus(const std::string& statut)
{
	if (statut == "available")
		m_mediatheque->showdmedia(m_mediatheque->Findmediabystatus(available));
	if (statut == "borrowed")
		m_mediatheque->showdmedia(m_mediatheque->Findmediabystatus(borrowed));
}

void bibliothecaire::findbyname(const std::string& name)
{
	m_mediatheque->showdmedia(m_mediatheque->Findmediabytitle(name));
}

void bibliothecaire::findbytype(const std::string& type)
{
	if (type == "Book")
		m_mediatheque->showdmedia(m_mediatheque->FindBook(m_mediatheque->getallmedia()));
	if (type == "Film")
		m_mediatheque->showdmedia(m_mediatheque->FindFilm(m_mediatheque->getallmedia()));
	if (type == "VideoGame")
		m_mediatheque->showdmedia(m_mediatheque->FindVideoGame(m_mediatheque->getallmedia()));
}

//show

void bibliothecaire::showallmedia()
{
	m_mediatheque->showdmedia(m_mediatheque->getallmedia());
}

bibliothecaire::~bibliothecaire()
{
	delete m_mediatheque;
	m_mediatheque = nullptr;
}

inline bool bibliothecaire::Clientalereadyexist(const std::string& name, const std::string& firstname, const int& age, const std::string& address, const std::string& phoneNumber)
{
	return m_mediatheque->clientexists(name, firstname, age, address, phoneNumber);
}

inline bool bibliothecaire::Bookalreadeyexist(const std::string& Title, const std::string& ISBN)
{
	return m_mediatheque->Bookalreadeyexist(Title, ISBN);
}

inline bool bibliothecaire::Filmalreadeyexist(const std::string& Title, const Film_Support& support, const int& agerestriction)
{
	return m_mediatheque->Filmalreadeyexist(Title, support, agerestriction);
}

inline bool bibliothecaire::VideoGamealreadeyexist(const std::string& Title, const game_Studio& studio, const int& Pegi, const game_gender& gender)
{
	return m_mediatheque->VideoGamealreadeyexist(Title, studio, Pegi, gender);
}
