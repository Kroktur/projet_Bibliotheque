#pragma once
#include "Consoleframebuffer.h"
#include "ObjectV2.h"
#include <vector>

class MediaLibrary
{
public:
	//add Entity
	void addEntity(Entity* newEntity);
	//remove Entity
	void removeEntity(Entity* entityToDelete);
	void removeEntity(std::vector<Entity*> list);
	//check if the content is equal
	bool EntityBind(Entity* firstEntity, Entity* secondEntity);
	//find type
	std::vector<Entity*> findType(Entity_Type type,std::vector<Entity*> list);
	//cobine
	std::vector<Entity*> conbineList(std::vector<Entity*> list1, std::vector<Entity*> list2);
	//filtre
	std::vector<Entity*> FilterList(std::vector<Entity*> list1, std::vector<Entity*> list2);
	//full list
	std::vector<Entity*> getFullEntitylist();
	//show
	void ShowEntity(std::vector<Entity*> list,ConsoleFramebuffer* consol);
private:
	void ShowEntity(Entity* entity, ConsoleFramebuffer* consol);
	bool EntityBind(Entity* firstEntity, Entity* secondEntity, Entity_Type type);
	std::vector<Entity*> m_Entity;
};