#pragma once
#include "Entity.h"
#include "EntityBlueprint.h"
#include "Components/ComponentBuilder.h"

class Component;

namespace ECS
{
	using EntityType = std::string;
	using ComponentFactory = CU::Factory<ComponentBuilder, Component>;
}

// TODO: Store blueprints in ResourceHolder??
class EntityFactory : public Subscriber
{
public:
	EntityFactory();
	~EntityFactory();

	void Receive(Message& message) override;

	void LoadBlueprints(const std::string& path);
	//void LoadBlueprint(const std::string& aPath);

	void ConstructBlueprint(const rapidjson::Value& value);

	Entity Create(const ECS::EntityType& type);
	Entity CreateFromBlueprint(const EntityBlueprint& blueprint);

	void RegisterBlueprint(const std::string& id, EntityBlueprint blueprint);
	void RegisterComponentBuilder(const std::string& type, ComponentBuilder* builder);

private:
	ECS::ComponentFactory								m_componentFactory;
	std::unordered_map<std::string, EntityBlueprint>	m_blueprints;		
};