#pragma once
#include <string>
#include <iostream>
#include <map>
class Foo
{
public:
	static void display();
};

class GameObject
{
public:
	virtual ~GameObject() = default;
	virtual void description() = 0;
	virtual GameObject* clone() = 0;
};

class player : public GameObject
{
public:
	~player() override
	{
		std::cout << "Game over" << std::endl;
	}
	void description() override
	{
		std::cout << "je suis un player" << std::endl;
	}
	GameObject* clone() override
	{
		return new player;
	}
};

class Enemy : public GameObject
{
public:
	~Enemy() override = default;
	void description() override
	{
		std::cout << "je suis un ennemy" << std::endl;
	}
	GameObject* clone() override
	{
		return new Enemy;
	}
};
class Powerup : public GameObject
{
public:
	~Powerup() override = default;
	void description() override
	{
		std::cout << "je suis un powerup" << std::endl;
	}
	GameObject* clone() override
	{
		return new Powerup;
	}
};

template<typename Key, typename Value>
class Factory
{
public:
	using Registry = std::map<Key, Value*>;

	Factory() = default;

	~Factory()
	{
		for (auto& [key, value] : m_registry)
			delete value;

		m_registry.clear();
	}

	void registerType(const Key& key, Value* value)
	{
		if (m_registry.contains(key))
			return;

		m_registry.insert({ key, value });
	}

	Value* create(const Key& key)
	{
		if (auto it = m_registry.find(key); it == m_registry.end())
			return nullptr;
		else
			return it->second->clone();
	}

private:
	Registry m_registry;
};

class GameObjectFactory : public Factory<std::string, GameObject>
{
public:
	GameObjectFactory()
	{
		registerType("Player", new player);
		registerType("Enemy", new Enemy);
		registerType("PowerUp", new Powerup);
	}
};
