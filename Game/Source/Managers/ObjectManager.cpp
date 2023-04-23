#include "Pch.h"
#include "ObjectManager.h"
#include "Data/Constants.h"
#include "../Builders/ComponentBuilder.hpp"
#include "../GameObject/Components/Component.h"

#define PROTOTYPE_SIZE 100

CU::Factory<ComponentBuilder, Component>	ObjectManager::s_componentFactory;
std::unordered_map<std::string, GameObject>	ObjectManager::s_prototypes;


ObjectManager::ObjectManager()
{
	s_prototypes.reserve(PROTOTYPE_SIZE);
}

ObjectManager::~ObjectManager()
{
	s_prototypes.clear();
	Clear();
}

GameObject* ObjectManager::Create(const std::string& aType)
{
	assert(ContainsPrototype(aType) && "[ERROR]: couldn't find specified prototype");

	auto copy = s_prototypes[aType].Copy();
	m_gameObjects.push_back(copy);

	return &m_gameObjects.back();

	//return s_prototypes[aType].Copy();
}

GameObject* ObjectManager::Search(int anID)
{
	return nullptr;
}

void ObjectManager::AddObject(const GameObject& aGameObject)
{
	m_gameObjects.push_back(aGameObject);
	// Todo; set owner??
}

void ObjectManager::DestroyObject(GameObject* aGameObject)
{

}

void ObjectManager::DestroyAllObjects()
{

}

void ObjectManager::DestroyAllObjects(const std::string& aType)
{

}

//void ObjectManager::RegisterPrototype(const std::string& aType, const GameObject& aGameObject)
//{
//	assert(!ContainsPrototype(aType));
//
//	s_prototypes.insert({ aType, aGameObject });
//
//	// read from file...
//}



void ObjectManager::RemovePrototype(const std::string& aType)
{}

//void ObjectManager::LoadFromFile(const std::string& aPath)
//{
//	// load objects from file...
//
//
//	// pass in component type (string) to component factory...
//}


void ObjectManager::RegisterBuilder(const std::string& aType, ComponentBuilder* aBuilder)
{
	s_componentFactory.RegisterBuilder(aType, aBuilder);
}

void ObjectManager::RegisterPrototype(const std::string& aType, const GameObject& aGameObject)
{
	if (s_prototypes.find(aType) == s_prototypes.end())
		s_prototypes.insert({ aType, aGameObject });
}

void ObjectManager::LoadPrototypes(const std::string& aPath) 	// TODO; use parser in engine?
{
	std::ifstream ifs{ aPath };
	std::string content{ std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>() };

	rapidjson::Document document;
	assert(!document.Parse(content.c_str()).HasParseError() && "Failed to Parse");

	for (auto& prototype : document["prototypes"].GetArray())
	{
		std::string type = prototype["name"].GetString();
		GameObject gameObject;

		for (auto& component : prototype["components"].GetArray())
		{
			Component* comp = s_componentFactory.Build(component["type"].GetString());
			comp->Init(component);

			gameObject.AddComponent(comp);	// use memory pool?!
		}

		RegisterPrototype(type, gameObject);
	}
}

void ObjectManager::Clear()
{
	m_gameObjects.clear();
}

const std::vector<GameObject>& ObjectManager::GetAllObjects() const
{
	return m_gameObjects;
}

std::vector<GameObject>& ObjectManager::GetAllObjects()
{
	return m_gameObjects;
}

bool ObjectManager::ContainsPrototype(const std::string& aType)	const
{
	return false;
}

void ObjectManager::CreatePrototype()
{

}