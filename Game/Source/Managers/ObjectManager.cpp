#include "Pch.h"
#include "ObjectManager.h"
#include "Data/Constants.h"
#include "../Builders/ComponentBuilder.hpp"
#include "../GameObject/Components/Component.h"


#include "../GameObject/Components/Core/Transform/C_Transform.h"

#define PROTOTYPE_SIZE 100
#define OBJECT_SIZE 2000

CU::Factory<ComponentBuilder, Component>	ObjectManager::s_componentFactory;
std::unordered_map<std::string, GameObject>	ObjectManager::s_prototypes;


ObjectManager::ObjectManager()
{
	m_gameObjects.reserve(OBJECT_SIZE);
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

	// if no transform... add it...
	//if (copy.GetComponent<C_Transform>() == nullptr)
	//	copy.Ad

	m_gameObjects.push_back(std::move(copy));

	return &m_gameObjects.back();

	//return s_prototypes[aType].Copy();
	//return nullptr;
}

GameObject* ObjectManager::Find(unsigned anID)
{
	// sort array by number??

	auto iterator = std::find_if(m_gameObjects.begin(), m_gameObjects.end(), [=](const GameObject& aGameObject) { return aGameObject.GetID() == anID; });
	return &(*iterator); // WORKS??
}

void ObjectManager::AddObject(GameObject&& aGameObject)
{
	m_gameObjects.push_back(std::move(aGameObject));
	
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

void ObjectManager::RegisterPrototype(const std::string& aType, GameObject&& aGameObject)
{
	s_prototypes.insert_or_assign(aType, std::move(aGameObject));
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

		RegisterPrototype(type, std::move(gameObject));
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