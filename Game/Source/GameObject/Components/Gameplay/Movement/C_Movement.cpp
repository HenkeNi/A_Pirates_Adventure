#include "Pch.h"
#include "C_Movement.h"
#include "../GameObject/GameObject.h"
#include "../../Core/Transform/C_Transform.h"

C_Movement::C_Movement(GameObject* anOwner)
	: Component{ anOwner }, m_movementSpeed{ 2.f }
{
}

void C_Movement::Init(rapidjson::Value& aValue)
{
}

void C_Movement::HandleMessage(const CompMessage& aMsg)
{
	// if move up => vel.y = -1

	// 

}

void C_Movement::Update(float aDeltaTime)
{

	// Get direction() => normalize...



	// notify every frame, or just when changed..?

	m_transform->MoveBy(m_velocity * m_movementSpeed * aDeltaTime);
}

void C_Movement::LateUpdate(float aDeltaTime)
{
}

void C_Movement::OnActivate()
{
	m_transform = m_owner->GetComponent<C_Transform>();
}

C_Movement* C_Movement::Copy() const
{
	auto* res = CU::MemoryPool<C_Movement>::GetInstance().GetResource();	// TODO; register in ComponentManager?
	assert(res && "Memory Pool returned invalid memory");

	return new (res) C_Movement{ *this };
}