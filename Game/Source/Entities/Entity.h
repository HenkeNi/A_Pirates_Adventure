#pragma once

class ComponentBase;

namespace
{
	using ComponentsMap_t = std::unordered_map<std::type_index, ComponentBase*>;
}

class Entity
{
public:
	Entity();
	Entity(const Entity& anEntity)							= delete;
	Entity(Entity&& anEntity)								noexcept;
	~Entity();

	Entity&			operator=(const Entity& anEntity)		= delete;
	Entity&			operator=(Entity&& anEntity)			noexcept;

	unsigned		GetID()									   const;

	void			AddComponent(ComponentBase* aComponent);
	template		<typename T>
	bool			RemoveComponent();
	template		<typename T>
	T*				GetComponent();
	template		<typename T>
	const T*		GetComponent()							   const;	
	template		<typename... T>
	bool			HasComponents()							   const;

private:
	template		<typename T>
	bool			HasComponent()							   const;

	unsigned		GenerateID()							   const;
	void			OnDestroy();

	ComponentsMap_t	m_components;
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

	bool found = (it != m_components.end());
	// assert(found && "Couldn't find component!");

	if (found)
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
	bool found = (it != m_components.end());

	assert(found && "Couldn't find component!");

	if (found)
		return dynamic_cast<T*>(it->second);

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