#pragma once
#include "../ECS/Utility/ECSTypes.h"

namespace Hi_Engine
{
	// Store entity factory in game layer


	// Store Prefabs in resource holder?

	class EntityManager;
	class EntityFactory;
	class ComponentRegistry;

	class EntityPrefab
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
	};

	class EntityFactory
	{
	public:
		EntityFactory(EntityManager& entityManager, ComponentRegistry& componentRegistry); // TODO; dont pass in component regitry?
		~EntityFactory();

		void LoadPrefabs();
		void ConstructPrefab(const rapidjson::Value& value);

		std::optional<Entity> Create(const char* name);
		std::optional<Entity> CreateFromJson(const rapidjson::Value& value);

	private:
		std::unordered_map<std::string, EntityPrefab> m_prefabs;
		EntityManager& m_entityManager;
		ComponentRegistry& m_componentRegistry;
	};


	template<typename T>
	inline void EntityPrefab::AddProperties(const ComponentProperties& properties)
	{
		auto type = std::type_index(typeid(T));

		if (m_componentProperties.find(type) == m_componentProperties.end())
			m_componentProperties.insert_or_assign(type, properties);
	}

	template<typename T>
	inline const ComponentProperties& EntityPrefab::GetProperties() const
	{
		auto type = std::type_index(typeid(T));

		assert(m_componentProperties.find(type) != m_componentProperties.end() && "[EntityBlueprint - ERROR]: Properties not found!");

		return m_componentProperties[type];
	}
}