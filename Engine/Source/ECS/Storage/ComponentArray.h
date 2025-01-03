#pragma once
#include "../Utility/ECSTypes.h"

// TODO; 
//  * store "read" and "write" components separately (for multi threading system) 

namespace Hi_Engine
{
	class IComponentArray
	{
	public:
		IComponentArray() = default;
		virtual ~IComponentArray() = default;

		IComponentArray(const IComponentArray&) = delete;
		IComponentArray& operator=(const IComponentArray&) = delete;

		IComponentArray(IComponentArray&&) noexcept = default;
		IComponentArray& operator=(IComponentArray&&) noexcept = default;

		virtual void RemoveComponent(Entity entity) = 0;
	};

	template <typename T>
	class ComponentArray : public IComponentArray
	{
	public:
		ComponentArray();

		bool AddComponent(Entity entity, const T& component);
		void RemoveComponent(Entity entity) override;

		const std::vector<T>& GetComponents() const;
		std::vector<T>& GetComponents();

		const T* GetComponent(Entity entity) const;
		T* GetComponent(Entity entity);

		bool HasComponent(Entity entity) const;
		void ForEachComponent(const std::function<void(T&)>& callback);

	private:

		std::unordered_map<Entity, std::size_t> m_entityToIndexMap;
		std::unordered_map<std::size_t, Entity> m_indexToEntityMap;

		std::vector<T> m_components;
	};

#pragma region Templated_Methods

	template <typename T>
	ComponentArray<T>::ComponentArray()
	{
		m_components.reserve(MaxEntities);
	}

	template <typename T>
	bool ComponentArray<T>::AddComponent(Entity entity, const T& component)
	{
		if (HasComponent(entity))
		{
			std::cerr << "[ComponentArray::AddComponent] - Entity: " << entity << " already has component of type " << typeid(T).name() << "\n";
			return false;
		}

		std::size_t index = m_components.size();
		
		if (index >= MaxEntities)
		{
			std::cerr << "[ComponentArray::AddComponent] - component array at max capacity!\n";
			return false;
		}

		m_entityToIndexMap.insert_or_assign(entity, index);
		m_indexToEntityMap.insert_or_assign(index, entity);

		m_components.push_back(component);

		return true;
	}

	template <typename T>
	void ComponentArray<T>::RemoveComponent(Entity entity)
	{
		if (!HasComponent(entity))
		{
			std::cerr << "[ComponentArray::RemoveComponent] - Component of type " << typeid(T).name() << " not found for Entity: " << entity << "!\n";
			return;
		}

		std::size_t indexToRemove = m_entityToIndexMap[entity];
		std::size_t lastIndex = m_components.size() - 1;

		if (indexToRemove != lastIndex)
		{
			m_components[indexToRemove] = std::move(m_components[lastIndex]);
						
			Entity entityToMove = m_indexToEntityMap[lastIndex];
			m_entityToIndexMap[entityToMove] = indexToRemove;
			m_indexToEntityMap[indexToRemove] = entityToMove;
		}

		m_entityToIndexMap.erase(entity);
		m_indexToEntityMap.erase(lastIndex);

		m_components.pop_back();
	}

	template <typename T>
	const std::vector<T>& ComponentArray<T>::GetComponents() const
	{
		return m_components;
	}

	template <typename T>
	std::vector<T>& ComponentArray<T>::GetComponents()
	{
		return m_components;
	}

	template <typename T>
	const T* ComponentArray<T>::GetComponent(Entity entity) const
	{
		if (HasComponent(entity))
		{
			return &m_components[m_entityToIndexMap.at(entity)];
		}

		return nullptr;
	}
	
	template <typename T>
	T* ComponentArray<T>::GetComponent(Entity entity)
	{
		if (HasComponent(entity))
		{
			return &m_components[m_entityToIndexMap.at(entity)];
		}

		return nullptr;
	}

	template <typename T>
	bool ComponentArray<T>::HasComponent(Entity entity) const
	{
		if (m_entityToIndexMap.contains(entity))
		{
			std::size_t index = m_entityToIndexMap.at(entity);
			return index >= 0 && index < m_components.size();
		}

		return false;
	}

	template <typename T>
	void ComponentArray<T>::ForEachComponent(const std::function<void(T&)>& callback)
	{
		for (auto& component : m_components)
			callback(component);
	}

#pragma endregion Templated_Methods
}
