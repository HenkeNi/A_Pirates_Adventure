#include "Pch.h"
#include "C_PhysicalNeeds.h"


C_PhysicalNeeds::C_PhysicalNeeds(GameObject* anOwner)
	: Component{ anOwner }
{
}

void C_PhysicalNeeds::Init(rapidjson::Value& aValue)
{
}

void C_PhysicalNeeds::HandleMessage(const CompMessage& aMsg)
{
}

void C_PhysicalNeeds::Update(float aDeltaTime)
{
}

C_PhysicalNeeds* C_PhysicalNeeds::Copy() const
{
	auto* res = CU::MemoryPool<C_PhysicalNeeds>::GetInstance().GetResource();
	assert(res && "Memory Pool returned invalid memory");

	return new (res) C_PhysicalNeeds(*this);
}
