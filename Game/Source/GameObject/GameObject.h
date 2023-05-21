#pragma once
#include "../Data/Structs.h"

class Component;

namespace
{
	using Components_t = std::unordered_map<std::type_index, Component*>;
}

// TODO; implment on destroy function...
class GameObject
{
public:
	GameObject();
	GameObject(const GameObject& aGameObject)					 = delete;
	GameObject(GameObject&& aGameObject)						 noexcept;
	~GameObject();

	GameObject& operator=(const GameObject& aGameObject)		 = delete;
	GameObject& operator=(GameObject&& aGameObject)				 noexcept;

	void			Update(float aDeltaTime);
	void			LateUpdate(float aDeltaTime);
	void			Draw()											const;
	bool			IsMarkedForRemoval()							const;
	void			MarkForRemoval();
	void			NotifyComponents(const CompMessage& aMsg);
	void			AddComponent(Component* aComponent);

	void			Activate();
	void			Deactivate();
	int				GetID()											const;
	GameObject		Copy()											const;

	template		<typename T>
	bool			RemoveComponent();
	template		<typename T>
	T*				GetComponent();
	template		<typename T>
	const T*		GetComponent()									const;
	template		<typename T>
	bool			Contains()										const;

private:
	unsigned		GenerateID()									const;
	void			OnDestroy();

	Components_t	m_components;
	unsigned		m_ID;							
	bool			m_isMarkedForRemoval;
};

#pragma region METHOD_DEFINITIONS

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