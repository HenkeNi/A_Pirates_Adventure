#pragma once

class EntityFactory;

class EntityBlueprint
{
public:
	EntityBlueprint();
	~EntityBlueprint();

	void AddComponentData(const std::string& aType, const std::any& someData);
	void AddComponentType(const std::string& aType);


private:
	friend class EntityFactory;

	std::vector<std::string>					m_componentTypes;
	std::unordered_map<std::string, std::any>	m_componentData;
};