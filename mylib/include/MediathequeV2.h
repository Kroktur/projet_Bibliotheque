#pragma once

#include "ObjectV2.h"
#include <vector>

class MediaLibrary
{
public:
	//add Entity
	void addEntity(Entity* newEntity);
	//remove Entity
	void removeEntity(Entity* entityToDelete);
	bool EntityBind(Entity* firstEntity, Entity* secondEntity);
private:
	bool EntityBind(Entity* firstEntity, Entity* secondEntity, Entity_Type type);
	std::vector<Entity*> m_Entity;
};