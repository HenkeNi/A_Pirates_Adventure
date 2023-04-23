#pragma once
#include "../Data/Structs.h"

class Component;

// TODO; clean up (remove) some functions
// TODO; return a GameObject* in copy?

// Todo; delete copy constructor and copy assignment (will have same ID...)
// Consider a container of GameOjbect pointers instead,...

// Func for deleteing/removing all componetns`??

// DO update, draw etc in componentmangaer??
// Delete both copy constructor AND copy assignment??

class GameObject
{
	using Components_t = std::unordered_map<std::type_index, Component*>;	// Put elsewhere??

public:
	GameObject();
	GameObject(const GameObject& aGameObject);	// maybe delete?
	GameObject(GameObject&& aGameObject)						 noexcept;
	~GameObject();

	GameObject& operator=(const GameObject& aGameObject); // maybe delete?
	GameObject& operator=(GameObject&& aGameObject)				 noexcept;

	void			Update(float aDeltaTime);
	void			LateUpdate(float aDeltaTime);
	void			Draw()											const;
	bool			IsMarkedForRemoval()							const;
	void			MarkForRemoval();
	void			NotifyComponents(CompMessage aMessage);
	void			AddComponent(Component* aComponent);

	void			Activate();
	void			Deactivate();

	template		<typename T>
	T*				CreateComponent();
	template		<typename T, typename... Args>
	T*				CreateComponent(Args&&... args);
	template		<typename T>
	bool			RemoveComponent();
	template		<typename T>
	T*				GetComponent();
	template		<typename T>
	const T*		GetComponent()									const;
	GameObject		Copy()											const;

private:
	template		<typename T>
	bool			Contains()										const;
	unsigned		GenerateID()									const;

	Components_t	m_components;
	unsigned		m_ID;							// Will change when copying?, or have two objects with same...
	bool			m_isMarkedForRemoval;
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
		//return std::dynamic_pointer_cast<T>(component->second);
		return dynamic_cast<T*>(component->second);
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