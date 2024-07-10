#pragma once

namespace
{
	using ComponentData = std::unordered_map<std::string, std::any>;
}

class EntityFactory;

class EntityBlueprint
{
public:
	EntityBlueprint();
	~EntityBlueprint();

	void SetIdentifier(const std::string& identifier);
	void AddComponentData(const std::string& type, const ComponentData& data);

private:
	friend class EntityFactory;

	std::string m_identifier;
	std::unordered_map<std::string, ComponentData>	m_componentData;
};