#include "Pch.h"
#include "C_Camera.h"


C_Camera::C_Camera(GameObject* anOwner)
	: Component{ anOwner }
{
}

C_Camera::~C_Camera()
{
}

void C_Camera::Init(rapidjson::Value& aValue)
{
	auto pos = aValue["position"].GetObj();
	m_camera.SetPosition({ pos["x"].GetFloat(), pos["y"].GetFloat(), pos["z"].GetFloat() });

}

void C_Camera::HandleMessage(CompMessage aMessage)
{
	if (aMessage.m_type == eMessageType::PositionChanged)
	{
		auto newPosition = std::any_cast<CU::Vector3<float>>(aMessage.m_data);
		m_camera.SetPosition(newPosition);
	}
}

void C_Camera::Update(float aDeltaTime)
{
}

void C_Camera::OnActivate()
{
	Hi_Engine::SpriteRenderer::GetInstance().SetCamera(&m_camera);

	// Set camera position; or only do in update??
}

void C_Camera::OnDeactivate()
{
	Hi_Engine::SpriteRenderer::GetInstance().SetCamera(nullptr);
}

C_Camera* C_Camera::Copy() const
{
	auto* res = CU::MemoryPool<C_Camera>::GetInstance().GetResource();
	assert(res && "Memory Pool returned invalid memory");

	return new (res) C_Camera{ *this };
}
