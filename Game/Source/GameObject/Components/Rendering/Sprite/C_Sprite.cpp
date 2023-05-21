#include "Pch.h"
#include "C_Sprite.h"
#include "../GameObject/GameObject.h"
#include "../../Core/Transform/C_Transform.h"


namespace CU = CommonUtilities;


C_Sprite::C_Sprite(GameObject* anOwner)
	: Component{ anOwner }, m_transform{ nullptr }
{
}

C_Sprite::~C_Sprite()
{
}

void C_Sprite::Init(rapidjson::Value& aValue)
{
}

void C_Sprite::HandleMessage(const CompMessage& aMsg) {}

void C_Sprite::Update(float aDeltaTime) {}

void C_Sprite::Draw() const
{
	assert(m_transform && "Failed to render Sprite");

	auto* texture = m_material.GetTexture();
	auto* shader = m_material.GetShader();

	if (texture && shader)
	{

		auto pos = m_transform->GetPosition();
		auto scale = m_transform->GetScale();
		//Hi_Engine::Dispatcher::GetInstance().SendEventInstantly<Hi_Engine::RenderSpriteEvent>(Hi_Engine::SpriteRenderData{ &m_material, { pos.x, pos.y, pos.z }, { scale.x, scale.y }, m_transform->GetRotation()});
		Hi_Engine::BillboardRenderer::GetInstance().Render({ &m_material, { pos.x, pos.y, pos.z }, { scale.x, scale.y }, m_transform->GetRotation() });
	

	//	// TODO; fix new...
	//	Hi_Engine::Dispatcher::GetInstance().SendEventInstantly(new Hi_Engine::RenderSpriteEvent{ { &m_material->GetTexture(), &m_material->GetShader(), m_material->GetColor(), 
	//		m_transform->GetPosition(), m_transform->GetScale(), m_transform->GetRotation() } }); // Add event instantly??

	}

	// Send out an event (a draw-event)??-> dont know whicj layer were on... (negative...)!



	/*if (auto transform = m_transform.lock())*/
	//if (m_transform && m_texture)
	//{
	//	const auto& scale = m_transform->GetScale();		// Scale or size??

	//	// maybe don't pass itslef to sprite renderer??
	//	Hi_Engine::SpriteRenderer::GetInstance().Render({ *m_material->GetTexture(),  * m_texture,  m_color, m_transform->GetPosition(), {scale.x, scale.y, scale.z}, m_transform->GetRotation()});
	//}
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

void C_Sprite::SetMaterial(const Material& aMaterial)
{
	m_material = aMaterial;
}
const Material& C_Sprite::GetMaterial() const
{
	return m_material;
}