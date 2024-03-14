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

	void Receive(Message& aMsg) override;

	void LoadBlueprints(const std::string& aPath);
	//void LoadBlueprint(const std::string& aPath);

	void ConstructBlueprint(const rapidjson::Value& aValue);

	Entity Create(const ECS::EntityType& aType);
	Entity CreateFromBlueprint(const EntityBlueprint& aBlueprint);

	void RegisterBlueprint(const std::string& anID, EntityBlueprint aBlueprint);
	void RegisterComponentBuilder(const std::string& aType, ComponentBuilder* aBuilder);

private:
	ECS::ComponentFactory								m_componentFactory;
	std::unordered_map<std::string, EntityBlueprint>	m_blueprints;		
};