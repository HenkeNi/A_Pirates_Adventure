#pragma once
#include "Entity.h"
#include "../Blueprints/EntityBlueprint.h"
#include "../Builders/ComponentBaseBuilder.hpp"
//#include "../Prototypes/Prototypes.h"

class ComponentBaseBuilder;

namespace 
{
	using Identifier = const std::string;
}

// Make factory static instead (in EntityMangaer) rather than static members?
class EntityFactory
{
public:
	EntityFactory();
	~EntityFactory();

	Entity	Create(Identifier& aType)								const;	// Todo; fix!! 
	Entity	CreateFromBlueprint(const EntityBlueprint& aBlueprint)	const;

	void	RegisterBlueprint(Identifier& aType, EntityBlueprint aBlueprint);
	void	RegisterComponentBuilder(Identifier& aType, ComponentBaseBuilder* aBuilder);

private:

	std::unordered_map<std::string, EntityBlueprint>	m_blueprints;
	CU::Factory<ComponentBaseBuilder, ComponentBase>	m_componentFactory;


	// static class ComponentFactory* s_componentFactory;
};
