#include "Pch.h"
#include "C_Transform.h"
#include "../GameObject/GameObject.h"

namespace CU = CommonUtilities;


C_Transform::C_Transform(GameObject* anOwner)
	: Component{ anOwner }, m_currPosition{ 0.f, 0.f, 0.f }, m_prevPosition{ 0.f, 0.f, 0.f }, m_desiredPosition{ 0.f, 0.f, 0.f }, m_scale{1.f, 1.f, 1.f}, m_rotation{0.f}
{
}

C_Transform::~C_Transform()
{
	// unregiser component..
}

void C_Transform::Init(rapidjson::Value& aValue)
{
	// TODO: Check if contains members???

	auto pos = aValue["position"].GetObj();
	m_currPosition = { pos["x"].GetFloat(), pos["y"].GetFloat(), pos["z"].GetFloat() };

	auto scale = aValue["scale"].GetObj();
	m_scale = { scale["x"].GetFloat(), scale["y"].GetFloat(), scale["z"].GetFloat() };
	
	m_rotation = { aValue["rotation"].GetFloat() };

	m_desiredPosition = m_prevPosition = m_currPosition;
}

void C_Transform::HandleMessage(const CompMessage& aMsg) 
{
	// Listen to should stop??
}

void C_Transform::Update(float aDeltaTime)
{
	// m_prevPosition = m_currPosition;  // make sure position isn't update before...

	/*if (m_owner->GetID() == 2)
		std::cout << "Pos: " << m_currPosition.x << ", " << m_currPosition.y << ", " << m_currPosition.z << '\n';*/

	if (HasMoved() && m_owner)
		m_owner->NotifyComponents({ eComponentMessage::PositionChanged, m_currPosition });
}

void C_Transform::LateUpdate(float aDeltaTime)
{
	m_prevPosition = m_currPosition;
}

C_Transform* C_Transform::Copy() const
{
	auto* res = CU::MemoryPool<C_Transform>::GetInstance().GetResource();	// TODO; register in ComponentManager?
	assert(res && "Memory Pool returned invalid memory");

	return new (res) C_Transform{ *this };
}

void  C_Transform::SetPosition(const CU::Vector3<float>& aPosition)
{
	m_currPosition = aPosition;
}

void  C_Transform::SetPosition(float aX, float aY, float aZ)
{
	m_currPosition = { aX, aY, aZ };
}

void  C_Transform::SetXPosition(float aX)
{
	m_currPosition.x = aX;
}

void  C_Transform::SetYPosition(float aY)
{
	m_currPosition.y = aY;
}

void C_Transform::SetZPosition(float aZ)
{
	m_currPosition.z = aZ;
}

void C_Transform::SetScale(const CU::Vector3<float>& aScale)
{
	m_scale = aScale;
}

void C_Transform::SetRotation(float aRotation)
{
	m_rotation = aRotation;
}

void  C_Transform::MoveBy(const CU::Vector3<float>& anOffset)
{
	m_currPosition += anOffset;
}

void  C_Transform::MoveBy(float anOffsetX, float anOffsetY, float anOffsetZ)
{
	m_currPosition.x += anOffsetX;
	m_currPosition.y += anOffsetY;
	m_currPosition.z += anOffsetZ;
}

const CU::Vector3<float>& C_Transform::GetPosition() const
{
	return m_currPosition;
}

const CU::Vector3<float>& C_Transform::GetScale() const
{
	return m_scale;
}

float C_Transform::GetRotation() const
{
	return m_rotation;
}

bool  C_Transform::HasMoved() const
{
	return m_prevPosition != m_currPosition;
}