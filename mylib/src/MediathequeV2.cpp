#include "MediathequeV2.h"

void MediaLibrary::addEntity(Entity* newEntity)
{
	m_Entity.push_back(newEntity);
}

void MediaLibrary::removeEntity(Entity* entityToDelete)
{
	/*for (auto it = m_Entity.begin(); it != m_Entity.end(); )
	{
		bool found = false;
		if (clientbind(*it, clientToDelete))
		{
				found = true;
				break;
		}
		
		if (found)
		{
			delete* it;
			it = m_client.erase(it);
		}
		else
			++it;
	}*/
}

bool MediaLibrary::EntityBind(Entity* firstEntity, Entity* secondEntity)
{
	if (firstEntity->getType() != secondEntity->getType())
		return false;
	return EntityBind(firstEntity, secondEntity, firstEntity->getType());	
}

bool MediaLibrary::EntityBind(Entity* firstEntity, Entity* secondEntity, Entity_Type type)
{
	
	if (type == Client_Type)
	{
		if (*static_cast<Client*>(firstEntity) == *static_cast<Client*>(secondEntity))
			return true;
	}
	return false;

}
