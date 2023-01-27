#pragma once
#include "../Data/Enumerations.h"

class Component;


class GameObject
{
	using ComponentContainer_t = std::unordered_map<std::type_index, std::shared_ptr<Component>>;

public:
	GameObject();
	GameObject(const GameObject& aGameObject);
	GameObject(GameObject&& aGameObject)												 noexcept;
	~GameObject();

	GameObject& operator=(const GameObject& aGameObject);
	GameObject& operator=(GameObject&& aGameObject)										 noexcept;

	void						Update(float aDeltaTime);
	void						LateUpdate(float aDeltaTime);
	void						Draw()														const;
	bool						IsMarkedForRemoval()										const;
	void						SetIsMarkedForRemoval(bool isMarked);
	void						NotifyComponents(eCompMessage aMessageType, const std::any& someData);
	void						AddComponent(const std::shared_ptr<Component> aComponent);

	template					<typename T>
	std::shared_ptr<T>			CreateComponent();
	template					<typename T, typename... Args>
	std::shared_ptr<T>			CreateComponent(Args&&... args);
	template					<typename T>
	bool						RemoveComponent();
	template					<typename T>
	std::shared_ptr<T>			GetComponent();
	template					<typename T>
	const std::shared_ptr<T>	GetComponent()												const;

private:
	template					<typename T>
	bool						Contains()													const;
	unsigned					GenerateID()												const;

	ComponentContainer_t		m_components;
	unsigned					m_ID;
	bool						m_isMarkedForRemoval;
};

#pragma region Method_Definitions

template <typename T>
std::shared_ptr<T> GameObject::CreateComponent()
{
	assert(!Contains<T>() && "GameObject already contains component");

	auto component = std::make_shared<T>(this);
	m_components[std::type_index(typeid(T))] = component;

	return component;
}

template <typename T, typename... Args>
std::shared_ptr<T> GameObject::CreateComponent(Args&&... args)
{
	assert(!Contains<T>() && "GameObject already contains component");

	auto component = std::make_shared<T>(this, std::forward<Args>(args)...);
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
std::shared_ptr<T> GameObject::GetComponent()
{
	auto component = m_components.find(std::type_index(typeid(T)));
	if (component != m_components.end())
	{
		return std::dynamic_pointer_cast<T>(component->second);
	}

	return nullptr;
}

template <typename T>
const std::shared_ptr<T> GameObject::GetComponent() const
{
	return GetComponent();
}

template <typename T>
bool GameObject::Contains() const
{
	return m_components.find(std::type_index(typeid(T))) != m_components.end();
}

#pragma endregion Method_Definitions