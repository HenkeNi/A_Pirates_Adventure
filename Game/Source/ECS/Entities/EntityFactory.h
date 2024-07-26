#pragma once
#//include "Entity.h"
#include "EntityBlueprint.h"
#include "ECSTypes.h"

class Component;

namespace 
{
	//using EntityType = std::string;
	//using ComponentFactory = CU::Factory<ComponentBuilder, Component>;
}

class ECS;

// TODO: Store blueprints in ResourceHolder??
class EntityFactory
{
public:
	EntityFactory(ECS& ecs);
	~EntityFactory();

	// static ComponentProperties ParseComponent(const rapidjson::Value& value); //  dont static?

	void LoadBlueprint(const std::string& path);
	void ConstructBlueprint(const rapidjson::Value& value);

	Entity Create(const char* name);
	Entity Create(const char* name, const rapidjson::Value& value);
	//Entity CreateFromBlueprint(const EntityBlueprint& blueprint);

	//template <typename T>
	//void RegisterComponentBuilder(const std::string& type);
	void RegisterBlueprint(const std::string& id, EntityBlueprint blueprint);

	// TEST
	// inline Hi_Engine::Factory<ComponentBuilder, Component>& GetCompFactory() { return m_componentFactory; }

private:
	// Hi_Engine::Factory<ComponentBuilder, Component>     m_componentFactory; // remove!
	std::unordered_map<std::string, EntityBlueprint>	m_blueprints; // BlueprintManager?



	ECS& m_ecs; // pass in EntityManager/ComponentManager instead?
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