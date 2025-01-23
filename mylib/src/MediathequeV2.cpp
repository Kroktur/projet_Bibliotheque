#include "MediathequeV2.h"

void MediaLibrary::addEntity(Entity* newEntity)
{
	m_Entity.push_back(newEntity);
}

void MediaLibrary::removeEntity(Entity* entityToDelete)
{
	for (auto it = m_Entity.begin(); it != m_Entity.end(); )
	{
		bool found = false;
		if (EntityBind(*it, entityToDelete))
		{
				found = true;
				break;
		}
		
		if (found)
		{
			delete* it;
			it = m_Entity.erase(it);
		}
		else
			++it;
	}
}

void MediaLibrary::removeEntity(std::vector<Entity*> list)
{
	for (auto& listidx : list)
		removeEntity(listidx);
}

bool MediaLibrary::EntityBind(Entity* firstEntity, Entity* secondEntity)
{
	if (firstEntity->getType() != secondEntity->getType())
		return false;
	return EntityBind(firstEntity, secondEntity, firstEntity->getType());	
}

std::vector<Entity*> MediaLibrary::findType(Entity_Type type, std::vector<Entity*> list)
{
	std::vector<Entity*> result;
	for (auto& listidx : list)
	{
		if (type == Client_Type && listidx->getType() == Client_Type)
			result.push_back(listidx);
		if (type == Book_Type && listidx->getType() == Book_Type)
			result.push_back(listidx);
		if (type == Film_Type && listidx->getType() == Film_Type)
			result.push_back(listidx);
		if (type == VideGame_Type && listidx->getType() == VideGame_Type)
			result.push_back(listidx);
	}
	return result;
}

std::vector<Entity*> MediaLibrary::conbineList(std::vector<Entity*> list1, std::vector<Entity*> list2)
{
	std::vector<Entity*> result;
	for (auto& listidx : list1)
	{
		result.push_back(listidx);
	}
	

	for (auto& listidx2 : list2)
	{
		bool find = false;
		for (auto& listidx: list1)
		{
			if (EntityBind(listidx, listidx2))
			{
				find = true;
				break;
			}
		}
		if(!find)
		result.push_back(listidx2);
	}
	return result;
}

std::vector<Entity*> MediaLibrary::FilterList(std::vector<Entity*> list1, std::vector<Entity*> list2)
{
	std::vector<Entity*> result;
	for (auto& listidx : list1)
	{
		bool find = false;
		for (auto& listidx2 : list2)
		{
			if (EntityBind(listidx, listidx2))
				find = true;
		}
		if (find)
			result.push_back(listidx);
	}	
	return result;
}

std::vector<Entity*> MediaLibrary::getFullEntitylist()
{
	return m_Entity;
}

void MediaLibrary::ShowEntity(std::vector<Entity*> list, ConsoleFramebuffer* consol)
{
	for (auto& idx : list)
		ShowEntity(idx, consol);
}

MediaLibrary::~MediaLibrary()
{
	for (auto& idx : m_Entity)
	{
		delete idx;
		idx = nullptr;
	}
	m_Entity.clear();
}

std::vector<Entity*> MediaLibrary::Search(std::vector<Entity*> list, search Search, std::string reSearch)
{
	std::vector<Entity*> result;
	if (Search == Name_Search)
	{
		list = findType(Client_Type, list);
		for (auto& idx : list)
		{
			if (static_cast<Client*>(idx)->getName() == reSearch)
				result.push_back(idx);
		}
	}
	if (Search == FirstName_Search)
	{
		list = findType(Client_Type, list);
		for (auto& idx : list)
		{
			if (static_cast<Client*>(idx)->getFirstName() == reSearch)
				result.push_back(idx);
		}
	}
	if (Search == Age_Search)
	{
		list = findType(Client_Type, list);
		for (auto& idx : list)
		{
			if (static_cast<Client*>(idx)->getAge() == reSearch)
				result.push_back(idx);
		}
	}
	if (Search == EmailAddress_Search)
	{
		list = findType(Client_Type, list);
		for (auto& idx : list)
		{
			if (static_cast<Client*>(idx)->getEmailAddress() == reSearch)
				result.push_back(idx);
		}
	}
	if (Search == PhoneNumber_Search)
	{
		list = findType(Client_Type, list);
		for (auto& idx : list)
		{
			if (static_cast<Client*>(idx)->getPhoneNumber() == reSearch)
				result.push_back(idx);
		}
	}
	if (Search == Title_Search)
	{
		list = conbineList(findType(Film_Type, list), conbineList(findType(VideGame_Type, list), findType(Book_Type, list)));
		for (auto& idx : list)
		{
			if (static_cast<IMedia*>(idx)->getTitle() == reSearch)
				result.push_back(idx);
		}
	}
	if (Search == ISBN_Search)
	{
		list = findType(Book_Type, list);
		for (auto& idx : list)
		{
			if (static_cast<Book*>(idx)->getISBN() == reSearch)
				result.push_back(idx);
		}
	}
	if (Search == Support_Search)
	{
		list = findType(Film_Type, list);
		for (auto& idx : list)
		{
			if (static_cast<Film*>(idx)->getSupport() == reSearch)
				result.push_back(idx);
		}
	}
	if (Search == AgeRestriction_Search)
	{
		list = findType(Film_Type, list);
		for (auto& idx : list)
		{
			if (static_cast<Film*>(idx)->getAgeRestriction() == reSearch)
				result.push_back(idx);
		}
	}
	if (Search == Studio_Search)
	{
		list = findType(VideGame_Type, list);
		for (auto& idx : list)
		{
			if (static_cast<VideoGame*>(idx)->getStudio() == reSearch)
				result.push_back(idx);
		}
	}
	if (Search == Pegi_Search)
	{
		list = findType(VideGame_Type, list);
		for (auto& idx : list)
		{
			if (static_cast<VideoGame*>(idx)->getPegi() == reSearch)
				result.push_back(idx);
		}
	}
	if (Search == Gender_Search)
	{
		list = findType(VideGame_Type, list);
		for (auto& idx : list)
		{
			if (static_cast<VideoGame*>(idx)->getGender() == reSearch)
				result.push_back(idx);
		}
	}
	if (Search == Status_Search)
	{
		Media_Status status = Invalid_Status;
		if (reSearch == "Available")
			status = Available_Status;
		if (reSearch == "Borrowed")
			status = Borrowed_Status;
		list = conbineList(findType(Film_Type, list), conbineList(findType(VideGame_Type, list), findType(Book_Type, list)));
		for (auto& idx : list)
		{
			if (static_cast<IMedia*>(idx)->getMediaStatus() == status)
				result.push_back(idx);
		}
	}
	return result;
}

void MediaLibrary::rentMedia(Client* client, std::vector<Entity*> list)
{
	client->rentMedia(list);
}

void MediaLibrary::returnMedia(Client* client, std::vector<Entity*> list)
{
	std::vector<Entity*> clientlist = client->getMedia();
	for (auto& clientidx : clientlist)
	{
		for (auto& idx : list)
		{
			if (EntityBind(clientidx, idx))
				client->removeMedia(clientidx);
		}
	}
}


void MediaLibrary::ShowEntity(Entity* entity, ConsoleFramebuffer* consol)
{
	entity->Render(consol);
}

bool MediaLibrary::EntityBind(Entity* firstEntity, Entity* secondEntity, Entity_Type type)
{	
	if (type == Client_Type)
	{
		if (*static_cast<Client*>(firstEntity) == *static_cast<Client*>(secondEntity))
			return true;
	}
	if (type == Book_Type)
	{
		if (*static_cast<Book*>(firstEntity) == *static_cast<Book*>(secondEntity))
			return true;
	}
	if (type == Film_Type)
	{
		if (*static_cast<Film*>(firstEntity) == *static_cast<Film*>(secondEntity))
			return true;
	}
	if (type == VideGame_Type)
	{
		if (*static_cast<VideoGame*>(firstEntity) == *static_cast<VideoGame*>(secondEntity))
			return true;
	}
	return false;

}
