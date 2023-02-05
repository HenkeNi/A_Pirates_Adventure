#include "Pch.h"
#include "Blueprint.h"
#include "../GameObject/Components/Component.h"
#include "../GameObject/GameObject.h"
#include "../Factories/ComponentFactory.h"


Blueprint::Blueprint()
{
}

Blueprint::~Blueprint()
{
	//for (auto& component : m_components)
		//delete component;
}

GameObject Blueprint::Create(const ComponentFactory& aFactory) const
{
	// Singleton component factory??
	GameObject gameObject;

	for (const auto& component : m_components)
	{
		gameObject.AddComponent(component->Copy());
	//	// Copy component...
	}

	return gameObject;
}



void Blueprint::LoadFromJson(rapidjson::Value& aBlueprintObject, ComponentFactory& aFactory)
{
	m_name = aBlueprintObject["name"].GetString();

	if (auto components = aBlueprintObject.FindMember("components") != aBlueprintObject.MemberEnd())
	{
		for (auto& value : aBlueprintObject["components"].GetArray())
		{
			std::string type = value["type"].GetString();

			if (auto component = aFactory.CreateComponent(type))
			{
				component->Init(value);
				Insert(component);
			}
			//Insert(type, aFactory.CreateComponent(type));
		}
	}
}

void Blueprint::Insert(Component* aComponent)
{
	assert(!Contains(aComponent));
	m_components.push_back(aComponent);
}

//void Blueprint::Insert(const std::string& aType, Component* aComponent)
//{
//	assert(!Contains(aType));
//
//	m_components.insert(std::make_pair(aType, aComponent));
//}

bool Blueprint::Contains(Component* aComponent) const
{
	return std::find(m_components.begin(), m_components.end(), aComponent) != m_components.end();
	//return m_components.find(aType) != m_components.end();
}