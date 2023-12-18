#pragma once

namespace ECS
{
	using ComponentData = std::unordered_map<std::string, std::any>;
}

class EntityFactory;

class EntityBlueprint
{
public:
	EntityBlueprint();
	~EntityBlueprint();

	void SetIdentifier(const std::string& anIdentifier);
	void AddComponentData(const std::string& aType, const ECS::ComponentData& someData);

private:
	friend class EntityFactory;

	std::string m_identifier;
	std::unordered_map<std::string, ECS::ComponentData>	m_componentData;
};