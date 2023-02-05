#pragma once
#include "Blueprints/SceneBlueprint.h"

class GameObject;

class SceneFactory
{
public:
	SceneFactory(const SceneFactory&)				= delete;
	SceneFactory& operator=(const SceneFactory&)	= delete;

	static SceneFactory&		GetInstance();

	std::vector<GameObject>		Create(const std::string& aType)										const;

	void						LoadBlueprints(const std::string& aFilepath);
	void						InsertBlueprint(const std::string& aKey, SceneBlueprint aBlueprint);
	bool						ContainsBlueprint(const std::string& aKey)								const;

private:
	SceneFactory();

	std::vector<SceneBlueprint> m_blueprints; 
};