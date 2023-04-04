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
}

void C_Camera::HandleMessage(eCompMessage aMessage)
{
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

C_Camera* C_Camera::Copy()
{
	return new C_Camera{ *this };
}
