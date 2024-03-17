#pragma once

class Component;

namespace ECS
{
	using Components = std::unordered_map<std::type_index, Component*>;
}

class Entity
{
public:
	Entity();
	Entity(const Entity&)							 = delete;
	Entity(Entity&& entity)							 noexcept;
	~Entity();

	Entity&		operator=(const Entity&)			 = delete;
	Entity&		operator=(Entity&& entity)			 noexcept;

	unsigned	GetID()									const;
	bool		AddComponent(Component* component);

	template	<typename T>
	bool		RemoveComponent();
	template	<typename T>
	T*			GetComponent();
	template	<typename T>
	const T*	GetComponent()						    const;	
	template	<typename... T>
	bool		HasComponents()							const;
	template	<typename T>
	bool		HasComponent()							const;

private:
	void		OnDestroy();

	ECS::Components	m_components;
	unsigned		m_ID;
};

#pragma region Method_Definitions

template <typename T>
bool Entity::RemoveComponent()
{
	return m_components.erase(std::type_index(typeid(T))) > 0;
}

template <typename T>
T* Entity::GetComponent()
{
	auto it = m_components.find(std::type_index(typeid(T)));
	if (it != m_components.end())
	{
		//return std::dynamic_pointer_cast<T>(component->second);
		return dynamic_cast<T*>(it->second);
	}
	return nullptr;
}

template <typename T>
const T* Entity::GetComponent() const
{
	auto it = m_components.find(std::type_index(typeid(T)));
	if (it != m_components.end())
	{
		//return std::dynamic_pointer_cast<T>(component->second);
		return dynamic_cast<T*>(it->second);
	}
	return nullptr;
}

template <typename... T>
bool Entity::HasComponents() const
{
	return (HasComponent<T>() && ...);
}

template <typename T>
bool Entity::HasComponent() const
{
	return m_components.find(std::type_index(typeid(T))) != m_components.end();
}

#pragma endregion Method_Definitions