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

	void SetIdentifier(const std::string& anIdentifier)
	{
		m_identifier = anIdentifier;
	}

	void AddComponent(const std::string& aType, const ComponentData& someData)
	{
		m_componentData.insert_or_assign(aType, someData);

		//m_componentData.insert_or_assign(aType, )

		//auto component = m_componentData.find(aType);

		//if (component == m_componentData.end())
		//	m_componentData.insert(aType);

		//m_components.insert_or_assign(aType, someData);
	}

	//void AddComponentData(const std::string& aType, const std::any& someData);
	// void AddComponentType(const std::string& aType);


private:
	friend class EntityFactory;

	std::string m_identifier;
	std::unordered_map<std::string, ComponentData>	m_componentData;



	//std::unordered_map<std::string, std::any>	m_components;
	//std::unordered_map<std::string, rapidjson::Value> m_components; // rename componentData



	// std::vector<std::string>					m_componentTypes;
	//std::unordered_map<std::string, std::any>	m_componentData;
};