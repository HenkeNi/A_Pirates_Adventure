#include "Pch.h"
#include "GameObject.h"
#include "Components/Component.h"
#include "Components/Core/Transform/C_Transform.h"


GameObject::GameObject()
	: m_isMarkedForRemoval{ false }, m_ID{ GenerateID() }
{
	m_components.reserve(16);
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
	OnDestroy();
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
		if (component.second)
			component.second->Update(aDeltaTime);
	}
}

void GameObject::LateUpdate(float aDeltaTime)
{
	for (auto& component : m_components)
	{
		if (component.second)
			component.second->LateUpdate(aDeltaTime);
	}
}

void GameObject::Draw() const
{
	for (auto& component : m_components)
	{
		if (component.second)
			component.second->Draw();
	}
}

bool GameObject::IsMarkedForRemoval() const
{
	return m_isMarkedForRemoval;
}

void GameObject::MarkForRemoval()
{
	m_isMarkedForRemoval = true;
}

void GameObject::NotifyComponents(const CompMessage& aMsg)
{
	for (auto& component : m_components)
	{
		if (component.second)
			component.second->HandleMessage(aMsg);
	}
}

void GameObject::AddComponent(Component* aComponent)
{
	if (!aComponent)
		return;

	auto type		= std::type_index(typeid(*aComponent));
	bool contains	= m_components.find(type) != m_components.end();

	assert(!contains && "Error: Trying to add a component that already exist in the GameObject!");

	aComponent->SetOwner(this);
	m_components.insert({ type, aComponent });
}

void GameObject::Activate()
{
	for (auto& component : m_components)
		component.second->OnActivate();
}

void GameObject::Deactivate()
{
	for (auto& component : m_components)
		component.second->OnDeactivate();
}

int GameObject::GetID() const
{
	return m_ID;
}

GameObject GameObject::Copy() const
{
	GameObject gameObject;

	for (const auto& component : m_components)
	{
		auto* copy = component.second->Copy();
		gameObject.AddComponent(copy);
	}

	return gameObject;
}

unsigned GameObject::GenerateID() const
{
	static unsigned id = 0;
	return ++id;
}

void GameObject::OnDestroy()
{
	// [TODO]: Cleanup? .. notify components?? Send back to memory pool??
}