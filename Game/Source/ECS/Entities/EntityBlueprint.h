#pragma once
#include "ECSTypes.h"


// BlueprintManager...

class EntityFactory;

class EntityBlueprint
{
public:

	void Init(const rapidjson::Value& value);

	template <typename T>
	void AddProperties(const ComponentProperties& properties);
	
	template <typename T>
	const ComponentProperties& GetProperties() const;

	inline const std::unordered_map<std::string, ComponentProperties>& GetComponentProperties() const { return m_componentProperties; }

	static Property ParseProperty(const rapidjson::Value& value); // FIX! put elsewhere??

private:
	friend class EntityFactory;

	std::unordered_map<std::string, ComponentProperties> m_componentProperties;

	// std::unordered_map<ComponentType, ComponentProperties> m_componentData; // use type index instead for type?
	// std::unordered_map<std::type_index, Component*> m_componentData;
};

template<typename T>
inline void EntityBlueprint::AddProperties(const ComponentProperties& properties)
{
	auto type = std::type_index(typeid(T));

	if (m_componentProperties.find(type) == m_componentProperties.end())
		m_componentProperties.insert_or_assign(type, properties);
}

template<typename T>
inline const ComponentProperties& EntityBlueprint::GetProperties() const
{
	auto type = std::type_index(typeid(T));

	assert(m_componentProperties.find(type) != m_componentProperties.end() && "[EntityBlueprint - ERROR]: Properties not found!");

	return m_componentProperties[type];
}
