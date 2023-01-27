#include "Pch.h"
#include "GameObject.h"
#include "Components/Component.h"
#include "Components/Transform/C_Transform.h"


GameObject::GameObject()
	: m_isMarkedForRemoval{ false }, m_ID{ GenerateID() }
{
	m_components.reserve(16);

	CreateComponent<C_Transform>();

	// Dispatcher::GetInstance().SendEvent({ eEvent::GameObjectCreated, this }); // TODO: Remove??
}

GameObject::GameObject(const GameObject& aGameObject)
	: m_isMarkedForRemoval{ false }, m_ID{ aGameObject.m_ID }
{
	for (auto& comp : aGameObject.m_components)
	{
		m_components[comp.first] = comp.second;
		m_components[comp.first]->SetOwner(this);
	}
}

GameObject::GameObject(GameObject&& aGameObject) noexcept
	: m_components{ std::move(aGameObject.m_components) }, m_ID{ aGameObject.m_ID }, m_isMarkedForRemoval{ aGameObject.m_isMarkedForRemoval }
{
	aGameObject.m_components.clear();

	for (auto& comp : m_components)
	{
		comp.second->SetOwner(this);
	}
}

GameObject::~GameObject()
{
	// [TODO]: Cleanup? .. notify components??
}

GameObject& GameObject::operator=(const GameObject& aGameObject)
{
	m_isMarkedForRemoval = aGameObject.m_isMarkedForRemoval;
	m_ID = aGameObject.m_ID;

	for (auto& comp : aGameObject.m_components)
	{
		m_components[comp.first] = comp.second;
		m_components[comp.first]->SetOwner(this);
	}

	return *this;
}

GameObject& GameObject::operator=(GameObject&& aGameObject) noexcept
{
	m_ID = aGameObject.m_ID;
	m_isMarkedForRemoval = aGameObject.m_isMarkedForRemoval;
	m_components = std::move(aGameObject.m_components);

	aGameObject.m_components.clear();

	for (auto& comp : m_components)
	{
		comp.second->SetOwner(this);
	}

	return *this;
}

void GameObject::Update(float aDeltaTime)
{
	for (auto& component : m_components)
	{
		if (component.second && component.second->IsActive())
			component.second->Update(aDeltaTime);
	}
}

void GameObject::LateUpdate(float aDeltaTime)
{
	for (auto& component : m_components)
	{
		if (component.second && component.second->IsActive())
			component.second->LateUpdate(aDeltaTime);
	}
}

void GameObject::Draw() const
{
	for (auto& component : m_components)
	{
		if (component.second && component.second->IsActive())
			component.second->Draw();
	}
}

bool GameObject::IsMarkedForRemoval() const
{
	return m_isMarkedForRemoval;
}

void GameObject::SetIsMarkedForRemoval(bool isMarked)
{
	m_isMarkedForRemoval = isMarked;
}

void GameObject::NotifyComponents(eCompMessage aMessageType, const std::any& someData)
{
	for (auto& component : m_components)
	{
		if (component.second && component.second->IsActive())
			component.second->HandleMessage(aMessageType, someData);
	}
}

void GameObject::AddComponent(const std::shared_ptr<Component> aComponent)
{
	assert(!Contains<Component>() && "GameObject already contains component");

	aComponent->SetOwner(this);
	m_components[std::type_index(typeid(Component))] = aComponent;
}

unsigned GameObject::GenerateID() const
{
	static unsigned id = 0;
	return ++id;
}