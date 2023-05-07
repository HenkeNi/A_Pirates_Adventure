#include "Pch.h"
#include "C_Camera.h"
#include "../GameObject/GameObject.h"
#include "../Transform/C_Transform.h"


C_Camera::C_Camera(GameObject* anOwner)
	: Component{ anOwner }, m_target{ nullptr }
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
	if (m_target)
	{
		auto targetPosition = m_target->GetComponent<C_Transform>()->GetPosition();
		targetPosition.y += 3.f;
		targetPosition.z += 5.f;

		std::cout << "Curr pos: " << targetPosition.x << ", " << targetPosition.y << ", " << targetPosition.z << '\n';

		m_camera.SetPosition(targetPosition);
		//m_camera.Move(targetPosition, aDeltaTime);

		// Move cameras transform?? or dont need a transform??

		//m_owner->GetComponent<C_Transform>()->SetPosition(targetPosition);
		//m_target->GetComponent<C_Transform>()->SetPosition(targetPosition);
		//m_camera.SetPosition({ targetPosition.x, 0.f, 0.f });
	}
}

void C_Camera::OnActivate()
{
	Hi_Engine::SpriteRenderer::GetInstance().SetCamera(&m_camera);

	// Set camera position; or only do in update??


	// fetch target (player?) from pullingstation??

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

void C_Camera::SetTarget(GameObject* aTarget)
{
	delete m_target;
	m_target = aTarget;
}
