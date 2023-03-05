#include "Pch.h"
#include "C_Sprite.h"
#include "../GameObject/GameObject.h"
#include "../Transform/C_Transform.h"


C_Sprite::C_Sprite(GameObject* anOwner)
	: Component{ anOwner }, m_transform{ nullptr }, m_texture{ nullptr }
{
}

C_Sprite::~C_Sprite()
{
}

void C_Sprite::Init(rapidjson::Value& aValue)
{
}

void C_Sprite::HandleMessage(eCompMessage aMessage) {}

void C_Sprite::Update(float aDeltaTime) {}

void C_Sprite::Draw() const
{
	/*if (auto transform = m_transform.lock())*/
	if (m_transform)
	{
		auto color = CU::Vector4<float>{ 1.f, 1.f, 1.f, 1.f };
		auto scale = CU::Vector2<float>{ m_transform->GetScale().x, m_transform->GetScale().y }; // Scale or size??
		auto pos = m_transform->GetPosition();

		Hi_Engine::SpriteRenderer::GetInstance().Render({ *m_texture, color, m_transform->GetPosition(), scale, m_transform->GetRotation() });
	}
}

void C_Sprite::OnActivate()
{
	m_transform = m_owner->GetComponent<C_Transform>();
}

C_Sprite* C_Sprite::Copy()
{
	return new C_Sprite{ *this };
}
