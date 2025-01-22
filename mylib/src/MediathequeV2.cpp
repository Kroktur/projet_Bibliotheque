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
