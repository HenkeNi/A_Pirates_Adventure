#pragma once
#include "EntityBlueprint.h"
#include "ECSTypes.h" // needed??

class EntityManager;
// class ComponentRegistry;

// TODO: Store blueprints in ResourceHolder??
class EntityFactory
{
public:
	EntityFactory(EntityManager& entityManager, ComponentRegistry& componentRegistry);
	~EntityFactory();

	void LoadBlueprints();

	// static ComponentProperties ParseComponent(const rapidjson::Value& value); //  dont static?

	// void LoadBlueprint(const std::string& path);
	void ConstructBlueprint(const rapidjson::Value& value);

	Entity Create(const char* name);
	Entity CreateFromJson(const rapidjson::Value& value);

	// Entity Create(const char* name, const rapidjson::Value& value);
	// Entity Create(const char* name, const ComponentProperties& properties);
	//Entity CreateFromBlueprint(const EntityBlueprint& blueprint);

	//template <typename T>
	//void RegisterComponentBuilder(const std::string& type);
	void RegisterBlueprint(const std::string& id, EntityBlueprint blueprint);

private:
	std::unordered_map<std::string, EntityBlueprint>	m_blueprints; // BlueprintManager?


	EntityManager& m_entityManager;
	ComponentRegistry& m_componentRegistry;
};


//#pragma region Method_Definitions
//
//template<typename T>
//inline void EntityFactory::RegisterComponentBuilder(const std::string& type)
//{
//	m_componentFactory.RegisterBuilder(type, new ConcreteComponentBuilder<T>{});
//}
//
//#pragma endregion Method_Definitions