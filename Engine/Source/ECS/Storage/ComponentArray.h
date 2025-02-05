#pragma once
#include "../Utility/ECSTypes.h"
#include "Utility/TypeTraits.h"
#include "Logging/Logger.h"

// TODO; 
// Rename ComponentStorage or ComponentContainer or rename SparseSet?

namespace Hi_Engine
{
	class IComponentArray : private NonCopyable
	{
	public:
		IComponentArray() = default;
		virtual ~IComponentArray() = default;

		IComponentArray(const IComponentArray&) = delete;
		IComponentArray& operator=(const IComponentArray&) = delete;

		IComponentArray(IComponentArray&&) noexcept = default;
		IComponentArray& operator=(IComponentArray&&) noexcept = default;

		virtual void RemoveComponent(Entity entity) = 0;
		virtual void Clear() = 0;
	};

	template <ComponentType T>
	class ComponentArray : public IComponentArray // rename SparseSet
	{
	public:
		ComponentArray();

		template <Callable Callback>
		void ForEachComponent(Callback&& callback);
		
		template <typename... Args>
		bool AddComponent(Entity entity, Args&&... args);
		void RemoveComponent(Entity entity) override;
		
		bool HasComponent(Entity entity) const;
		void Clear() override;

		const std::vector<T>& GetComponents() const;
		std::vector<T>& GetComponents();

		const T* GetComponent(Entity entity) const; // return std::optional<std::refrence_wrapper?>
		T* GetComponent(Entity entity);

	private:
		std::unordered_map<Entity, std::size_t> m_entityToIndexMap;
		std::unordered_map<std::size_t, Entity> m_indexToEntityMap; // NEED?
		
		std::array<std::size_t, MaxEntities> m_entityToIndex; // sparse

		std::vector<T> m_components; // packed 
	};

#pragma region Templated_Methods

	template <ComponentType T>
	ComponentArray<T>::ComponentArray()
	{
		m_components.reserve(MaxEntities);
	}

	template <ComponentType T>
	template<Callable Callback>
	void ComponentArray<T>::ForEachComponent(Callback&& callback)
	{
		std::for_each(m_components.begin(), m_components.end(), [](T& component) { callback(component); });

		//for (auto& component : m_components)
		//	callback(component);
	}

	template<ComponentType T>
	template<typename ...Args>
	inline bool ComponentArray<T>::AddComponent(Entity entity, Args && ...args)
	{
		if (HasComponent(entity))
		{
			Logger::LogError("[ComponentArray::AddComponent] - Entity: " + std::to_string(entity) + " already has component of type " + std::string(typeid(T).name()));
			return false;
		}

		std::size_t index = m_components.size();

		if (index >= MaxEntities)
		{
			Logger::LogError("[ComponentArray::AddComponent] - component array of type " + std::string(typeid(T).name()) + " at max capacity!");
			return false;
		}

		m_entityToIndexMap.insert_or_assign(entity, index);
		m_indexToEntityMap.insert_or_assign(index, entity);

		m_components.emplace_back(std::forward<Args>(args)...);

		return true;
	}

	template <ComponentType T>
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

	template <ComponentType T>
	bool ComponentArray<T>::HasComponent(Entity entity) const
	{
		if (m_entityToIndexMap.contains(entity))
		{
			std::size_t index = m_entityToIndexMap.at(entity);
			return index >= 0 && index < m_components.size();
		}

		return false;
	}

	template <ComponentType T>
	void ComponentArray<T>::Clear()
	{
		m_entityToIndexMap.clear();
		m_indexToEntityMap.clear();

		m_components.clear();
	}

	template <ComponentType T>
	const std::vector<T>& ComponentArray<T>::GetComponents() const
	{
		return m_components;
	}

	template <ComponentType T>
	std::vector<T>& ComponentArray<T>::GetComponents()
	{
		return m_components;
	}

	template <ComponentType T>
	const T* ComponentArray<T>::GetComponent(Entity entity) const
	{
		if (HasComponent(entity))
		{
			return &m_components[m_entityToIndexMap.at(entity)];
		}

		return nullptr;
	}
	
	template <ComponentType T>
	T* ComponentArray<T>::GetComponent(Entity entity)
	{
		if (HasComponent(entity))
		{
			return &m_components[m_entityToIndexMap.at(entity)];
		}

		return nullptr;
	}

#pragma endregion Templated_Methods
}
