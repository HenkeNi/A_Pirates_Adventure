#include "Pch.h"
#include "C_Transform.h"
#include "../GameObject/GameObject.h"


C_Transform::C_Transform(GameObject* anOwner)
	: Component{ anOwner }, m_currPosition{ 0.f, 0.f }, m_prevPosition{ 0.f, 0.f }, m_scale{ 1.f, 1.f }, m_rotation{ 0.f }
{
}

C_Transform::~C_Transform()
{
}

void  C_Transform::HandleMessage(eCompMessage aMessageType, const std::any& someData)
{
}

void  C_Transform::Update(float aDeltaTime)
{
	if (HasMoved() && m_owner)
		m_owner->NotifyComponents(eCompMessage::PositionChanged, m_currPosition);

	m_prevPosition = m_currPosition; // Do in late update?
}

void  C_Transform::LateUpdate(float aDeltaTime)
{
}

void  C_Transform::SetPosition(const CU::Vector2<float>& aPosition)
{
	m_currPosition = aPosition;
}

void  C_Transform::SetPosition(float aX, float aY)
{
	m_currPosition = { aX, aY };
}

void  C_Transform::SetXPosition(float aX)
{
	m_currPosition.x = aX;
}

void  C_Transform::SetYPosition(float aY)
{
	m_currPosition.y = aY;
}

void C_Transform::SetScale(const CU::Vector2<float>& aScale)
{
	m_scale = aScale;
}

void  C_Transform::AddPosition(const CU::Vector2<float>& aPosition)
{
	m_currPosition += aPosition;
}

void  C_Transform::AddPosition(float aX, float aY)
{
	m_currPosition.x += aX;
	m_currPosition.y += aY;
}

const CU::Vector2<float>& C_Transform::GetPosition() const
{
	return m_currPosition;
}

const CU::Vector2<float>& C_Transform::GetScale() const
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