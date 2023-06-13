#include "Pch.h"
#include "C_BoxCollider.h"


C_BoxCollider::C_BoxCollider(GameObject* anOwner)
{
}

C_BoxCollider::~C_BoxCollider()
{
}

void C_BoxCollider::Init(rapidjson::Value& aValue)					
{
}

void C_BoxCollider::HandleMessage(const CompMessage& aMsg)			
{
	//if (aMsg.m_messageType == eComponentMessage::PositionChanged)
		// m_aabb.Init();
}

void C_BoxCollider::Update(float aDeltaTime)						
{
}

void C_BoxCollider::LateUpdate(float aDeltaTime)					
{
}

void C_BoxCollider::Draw() const
{
	// Draw quad with texture, rotate it so paralell with ground..
}

C_BoxCollider* C_BoxCollider::Copy() const
{
	auto* res = CU::MemoryPool<C_BoxCollider>::GetInstance().GetResource();	// TODO; register in ComponentManager?
	assert(res && "Memory Pool returned invalid memory");

	return new (res) C_BoxCollider{ *this };
}