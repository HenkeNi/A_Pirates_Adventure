#pragma once
#include "Entity.h"
#include "EntityBlueprint.h"
#include "Components/ComponentBuilder.h"

class Component;

namespace ECS
{
	using EntityType = std::string;
	//using ComponentFactory = CU::Factory<ComponentBuilder, Component>;
}

// TODO: Store blueprints in ResourceHolder??
class EntityFactory
{
public:
	EntityFactory();
	~EntityFactory();

	static ECS::ComponentData ParseComponent(const rapidjson::Value& value);

	void LoadBlueprints(const std::string& path);
	//void LoadBlueprint(const std::string& aPath);
	void ConstructBlueprint(const rapidjson::Value& value);

	Entity Create(const ECS::EntityType& type);
	Entity CreateFromBlueprint(const EntityBlueprint& blueprint);

	template <typename T>
	void RegisterComponentBuilder(const std::string& type);
	void RegisterBlueprint(const std::string& id, EntityBlueprint blueprint);

	// void RegisterComponentBuilder(const std::string& type, ComponentBuilder* builder);

	// Function to modify/initialize component?

	// TEST
	inline Hi_Engine::Factory<ComponentBuilder, Component>& GetCompFactory() { return m_componentFactory; }

private:
	//ECS::ComponentFactory								m_componentFactory;
	Hi_Engine::Factory<ComponentBuilder, Component>			m_componentFactory;
	std::unordered_map<std::string, EntityBlueprint>	m_blueprints;		
};


#pragma region Method_Definitions

template<typename T>
inline void EntityFactory::RegisterComponentBuilder(const std::string& type)
{
	m_componentFactory.RegisterBuilder(type, new ConcreteComponentBuilder<T>{});
}

#pragma endregion Method_Definitions