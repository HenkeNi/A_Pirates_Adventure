#pragma once
#include "Blueprints/Blueprint.h"
#include "ComponentFactory.h"

class GameObject;

class GameObjectFactory
{
public:
	~GameObjectFactory();
	GameObjectFactory(const GameObjectFactory&)				= delete;
	GameObjectFactory& operator=(const GameObjectFactory&)	= delete;

	static GameObjectFactory&	GetInstance();

	GameObject					Create(const std::string& aType)									const;

	void						LoadBlueprints(const std::string& aFilepath);
	void						InsertBlueprint(const std::string& aKey, Blueprint aBlueprint);
	bool						ContainsBlueprint(const std::string& aKey)							const;

private:
	GameObjectFactory();

	std::unordered_map<std::string, Blueprint>	m_blueprints; 
	ComponentFactory							m_componentFactory;
};