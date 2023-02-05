#include "Pch.h"
#include "SceneFactory.h"
#include "../GameObject/GameObject.h"


SceneFactory::SceneFactory()
{
}

SceneFactory& SceneFactory::GetInstance()
{
	static SceneFactory instance;
	return instance;
}

std::vector<GameObject> SceneFactory::Create(const std::string& aType) const
{
	return {};
}

void SceneFactory::LoadBlueprints(const std::string& aFilepath)
{
}

void SceneFactory::InsertBlueprint(const std::string& aKey, SceneBlueprint aBlueprint)
{
}

bool SceneFactory::ContainsBlueprint(const std::string& aKey) const
{
	return false;
}
