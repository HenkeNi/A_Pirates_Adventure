#include "Pch.h"
#include "C_Sprite.h"
#include "../GameObject/GameObject.h"
#include "../Transform/C_Transform.h"

namespace CU = CommonUtilities;


C_Sprite::C_Sprite(GameObject* anOwner)
	: Component{ anOwner }, m_color{ 1.f, 1.f, 1.f, 1.f }, m_transform{ nullptr }, m_texture{ nullptr }
{
}

C_Sprite::~C_Sprite()
{
}

void C_Sprite::Init(rapidjson::Value& aValue)
{
}

void C_Sprite::HandleMessage(CompMessage aMessage) {}

void C_Sprite::Update(float aDeltaTime) {}

void C_Sprite::Draw() const
{
	assert(m_transform && m_texture && "Failed to render Sprite");

	/*if (auto transform = m_transform.lock())*/
	if (m_transform && m_texture)
	{
		const auto& scale = m_transform->GetScale();		// Scale or size??

		Hi_Engine::SpriteRenderer::GetInstance().Render({ *m_texture, m_color, m_transform->GetPosition(), { scale.x, scale.y }, m_transform->GetRotation() });
	}
}

void C_Sprite::OnActivate()
{
	m_transform = m_owner->GetComponent<C_Transform>();
}

C_Sprite* C_Sprite::Copy() const
{
	auto* res = CU::MemoryPool<C_Sprite>::GetInstance().GetResource();
	assert(res && "Memory Pool returned invalid memory");

	return new (res) C_Sprite{ *this };
}
