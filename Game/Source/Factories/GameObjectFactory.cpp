#include "Pch.h"
#include "GameObjectFactory.h"
#include "../GameObject/GameObject.h"


GameObjectFactory::GameObjectFactory()
{
}

GameObjectFactory::~GameObjectFactory()
{
}

GameObjectFactory& GameObjectFactory::GetInstance()
{
	static GameObjectFactory instance;
	return instance;
}

GameObject GameObjectFactory::Create(const std::string& aType) const
{
	assert(ContainsBlueprint(aType));

	return m_blueprints.at(aType).Create(m_componentFactory);
}

void GameObjectFactory::LoadBlueprints(const std::string& aFilepath)
{
	std::ifstream ifs{ aFilepath }; 
	std::string content{ std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>() };

	rapidjson::Document document;
	if (!document.Parse(content.c_str()).HasParseError())
	{
		for (auto& value : document["blueprints"].GetArray())
		{
			Blueprint blueprint;
			blueprint.LoadFromJson(value, m_componentFactory);

			InsertBlueprint(value["name"].GetString(), blueprint);
		}
	}
}

void GameObjectFactory::InsertBlueprint(const std::string& aKey, Blueprint aBlueprint)
{
	assert(!ContainsBlueprint(aKey));

	m_blueprints.insert(std::make_pair(aKey, aBlueprint));
}

bool GameObjectFactory::ContainsBlueprint(const std::string& aKey) const
{
	return m_blueprints.find(aKey) != m_blueprints.end();
}