#include "Pch.h"
#include "C_Camera.h"
#include "../GameObject/GameObject.h"
#include "../../Core/Transform/C_Transform.h"


C_Camera::C_Camera(GameObject* anOwner)
	: Component{ anOwner }, m_target{ nullptr }, m_targetOffset{ 0.f, 0.f, 2.f } //, m_camera{ { 800, 0, 0, 1400 } }
{
	// temp:
	m_camera.SetPosition({ 0.f, 0.f, 2.f });
}

C_Camera::~C_Camera()
{
}

void C_Camera::Init(rapidjson::Value& aValue)
{
	auto pos = aValue["position"].GetObj();
	m_camera.SetPosition({ pos["x"].GetFloat(), pos["y"].GetFloat(), pos["z"].GetFloat() });

}

void C_Camera::HandleMessage(const CompMessage& aMsg)
{
	if (aMsg.m_messageType == eComponentMessage::PositionChanged)
	{
		auto newPosition = std::any_cast<CU::Vector3<float>>(aMsg.m_data);
		m_camera.SetPosition({ newPosition.x, newPosition.y, newPosition.z });
	}
}

void C_Camera::Update(float aDeltaTime)
{
	if (!m_target)
		return;
	
		auto targetPosition = m_target->GetComponent<C_Transform>()->GetPosition();
		targetPosition += m_targetOffset;
		
		m_owner->GetComponent<C_Transform>()->SetPosition(targetPosition);


					
		//m_camera.SetPosition({ targetPosition.x, targetPosition.y, targetPosition.z });




		//std::cout << "Targ Pos: " << targetPosition.x << ", " << targetPosition.y << ", " << targetPosition.z << '\n';
		//std::cout << "TargetPos: " << targetPosition.x << ", " << targetPosition.y << ", " << targetPosition.z << '\n';
		//std::cout << "Target pos: " << targetPosition.x << ", " << targetPosition.y << ", " << targetPosition.z << '\n';



		// m_camera.Move(targetPosition, aDeltaTime);
		// move cameras transform?? or dont need a transform??

		//m_owner->GetComponent<C_Transform>()->SetPosition(targetPosition);
		//m_target->GetComponent<C_Transform>()->SetPosition(targetPosition);
		//m_camera.SetPosition({ targetPosition.x, 0.f, 0.f });	
}

void C_Camera::OnActivate()
{
	//Hi_Engine::SpriteRenderer::GetInstance().SetCamera(&m_camera);

	Hi_Engine::BillboardRenderer::GetInstance().SetCamera(&m_camera);

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
	m_target = aTarget;
}
