#pragma once
#include "../Storage/ComponentArray.h"
#include "../Utility/ECSTypes.h"

// TODO; add functions for serialize / deserialize all components?

namespace Hi_Engine
{
	template <typename... Components>
	class ComponentView;

	class ComponentManager
	{
	public:
		ComponentManager();
		~ComponentManager();

		template <typename T>
		void RegisterComponent(const char* name);
		
		template <typename T>
		void AddComponent(Entity entity);

		template <typename T>
		void RemoveComponent(Entity entity);

		void RemoveAllComponents(Entity entity);
		
		template <typename T>
		const std::vector<T>& GetComponents() const;
		
		template <typename T>
		std::vector<T>& GetComponents();
		
		template <typename T>
		const T* GetComponent(Entity entity) const;

		template <typename T>
		T* GetComponent(Entity entity);

		template <typename... T>
		std::vector<ComponentType> GetComponentTypes() const;

		template <typename T>
		ComponentType GetComponentType() const;

	private:
		template <typename... Components>
		friend class ComponentView;
		
		template <typename T>
		const ComponentArray<T>* FindComponentArray() const;

		template <typename T>
		ComponentArray<T>& GetComponentArray();

		ComponentArrays m_componentArrays;
		ComponentTypes m_componentTypes;
		ComponentType m_nextComponentType;
	};

#pragma region Templated_Methods

	template <typename T>
	void ComponentManager::RegisterComponent(const char* name)
	{
		auto type = std::type_index(typeid(T));

		assert(m_componentArrays.find(type) == m_componentArrays.end() && "[ComponentManager::RegisterComponent] - Error: Component type already registered!");

		m_componentArrays.insert({ type, std::make_unique<ComponentArray<T>>() });
		m_componentTypes.insert({ type, m_nextComponentType });

		++m_nextComponentType;
	}

	template<typename T>
	void ComponentManager::AddComponent(Entity entity)
	{
		GetComponentArray<T>().AddComponent(entity, T{}); // pass in just T??
	}

	template<typename T>
	void ComponentManager::RemoveComponent(Entity entity)
	{
		GetComponentArray<T>().RemoveComponent(entity);	
	}

	template <typename T>
	const std::vector<T>& ComponentManager::GetComponents() const
	{
		return GetComponentArray<T>().GetComponents();
	}

	template<typename T>
	std::vector<T>& ComponentManager::GetComponents()
	{
		return GetComponentArray<T>().GetComponents();
	}

	template <typename T>
	const T* ComponentManager::GetComponent(Entity entity) const
	{
		if (const auto* componentArray = FindComponentArray<T>())
		{
			return componentArray.GetComponent(entity);
		}

		return nullptr;
	}

	template <typename T>
	T* ComponentManager::GetComponent(Entity entity)
	{
		return GetComponentArray<T>().GetComponent(entity); // why not same as above???????
	}

	template<typename ...T>
	std::vector<ComponentType> ComponentManager::GetComponentTypes() const
	{
		std::vector<ComponentType> componentTypes;
		(componentTypes.push_back(GetComponentType<T>()), ...);

		return componentTypes;
	}

	template<typename T>
	ComponentType ComponentManager::GetComponentType() const
	{
		auto type = std::type_index(typeid(T));
		auto iterator = m_componentTypes.find(type);

		if (iterator != m_componentTypes.end())
		{
			return iterator->second;
		}

		std::cerr << "[ERROR - ComponentManager::GetComponentType] - ComponentType: " << typeid(T).name() << " not registered!";
		//assert(false && "[ERROR - ComponentManager::GetComponentType] - ComponentType: " << typeid(T).name() << " not registered!");
		return ComponentType();
	}

	template<typename T>
	const ComponentArray<T>* ComponentManager::FindComponentArray() const
	{
		auto type = std::type_index(typeid(T));

		auto iterator = m_componentArrays.find(type);
		if (iterator != m_componentArrays.end())
		{
			return static_cast<ComponentArray<T>*>(iterator->second.get());
		}

		return nullptr;
	}

	template <typename T>
	ComponentArray<T>& ComponentManager::GetComponentArray()
	{
		auto type = std::type_index(typeid(T));

		auto iterator = m_componentArrays.find(type);
		if (iterator == m_componentArrays.end())
		{
			auto componentArray = std::make_unique<ComponentArray<T>>();
			m_componentArrays.insert({ type, std::move(componentArray) });

			return static_cast<ComponentArray<T>&>(*m_componentArrays[type]);
		}

		return static_cast<ComponentArray<T>&>(*iterator->second);
	}

#pragma endregion Templated_Methods
}