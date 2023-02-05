#pragma once
#include "../Data/Enumerations.h"

class Component;


class GameObject
{
	using Components_t = std::unordered_map<std::type_index, Component*>;

public:
	GameObject();
	GameObject(const GameObject& aGameObject);
	GameObject(GameObject&& aGameObject)									 noexcept;
	~GameObject();

	GameObject& operator=(const GameObject& aGameObject);
	GameObject& operator=(GameObject&& aGameObject)							 noexcept;

	void			Update(float aDeltaTime);
	void			LateUpdate(float aDeltaTime);
	void			Draw()														const;
	bool			IsMarkedForRemoval()										const;
	void			SetMarkedForRemoval(bool isMarked);
	void			NotifyComponents(eMessageType aType, const std::any& someData);
	void			AddComponent(Component* aComponent);

	template		<typename T>
	T*				CreateComponent();
	template		<typename T, typename... Args>
	T*				CreateComponent(Args&&... args);
	template		<typename T>
	bool			RemoveComponent();
	template		<typename T>
	T*				GetComponent();
	template		<typename T>
	const T*		GetComponent()												const;

private:
	template		<typename T>
	bool			Contains()													const;
	unsigned		GenerateID()												const;

	Components_t	m_components;
	unsigned		m_ID;
	bool			m_markedForRemoval;
};

#pragma region METHOD_DEFINITIONS

template <typename T>
T* GameObject::CreateComponent()
{
	assert(!Contains<T>() && "GameObject already contains component");

	auto component = new T(this);
	m_components[std::type_index(typeid(T))] = component;

	return component;
}

template <typename T, typename... Args>
T* GameObject::CreateComponent(Args&&... args)
{
	assert(!Contains<T>() && "GameObject already contains component");

	auto component = new T{ this, std::forward<Args>(args)... };
	m_components[std::type_index(typeid(T))] = component;

	return component;
}

template <typename T>
bool GameObject::RemoveComponent()
{
	auto component = m_components.find(std::type_index(typeid(T)));
	if (component != m_components.end())
	{
		m_components.erase(component);
		return true;
	}

	return false;
}

template <typename T>
T* GameObject::GetComponent()
{
	auto component = m_components.find(std::type_index(typeid(T)));
	if (component != m_components.end())
	{
		return std::dynamic_pointer_cast<T>(component->second);
	}

	return nullptr;
}

template <typename T>
const T* GameObject::GetComponent() const
{
	return GetComponent();
}

template <typename T>
bool GameObject::Contains() const
{
	return m_components.find(std::type_index(typeid(T))) != m_components.end();
}

#pragma endregion METHOD_DEFINITIONS