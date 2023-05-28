#include "Pch.h"
#include "C_PlayerController.h"
#include "../GameObject/GameObject.h"
#include "../Physics/Movement/C_Movement.h"


C_PlayerController::C_PlayerController(GameObject* anOwner)
	: Component{ anOwner }, m_movement{ nullptr }
{
}

void C_PlayerController::Init(rapidjson::Value& aValue)
{

}

void C_PlayerController::HandleMessage(const CompMessage& aMsg)
{
}

void C_PlayerController::HandleEvent(Hi_Engine::KeyEvent& anEvent)
{
	// Maybe send event?? MoveLeft, and how hard the key is pressed?? or better to just call relevant component (Movemnt)

	//if (anEvent.GetKeyCode() == 1) // FIX... dont send keycodes??
	//{
	//	m_movement->m_velocity.x = -1;
	//}
	//else if (anEvent.GetKeyCode() == 2)
	//{
	//	m_movement->m_velocity.x = 1;
	//}
	//else if (anEvent.GetKeyCode() == 3)
	//{
	//	m_movement->m_velocity.y = -1;
	//}
	//else if (anEvent.GetKeyCode() == 4)
	//{
	//	m_movement->m_velocity.y = 1;
	//}
}


void C_PlayerController::Update(float aDeltaTime)	// TODO; use x and z later...
{
	//m_owner->NotifyComponents({ eMessageType::MoveLeft, 1.f });

	// TODO; remove later....
	if (Hi_Engine::InputHandler::IsKeyHeld(Hi_Engine::eInputType::Key_W) || 
		Hi_Engine::InputHandler::IsKeyPressed(Hi_Engine::eInputType::Key_W))
		m_movement->m_velocity.z = -1;
	else if (Hi_Engine::InputHandler::IsKeyHeld(Hi_Engine::eInputType::Key_S) || 
		Hi_Engine::InputHandler::IsKeyPressed(Hi_Engine::eInputType::Key_S))
		m_movement->m_velocity.z = 1;
	else
		m_movement->m_velocity.z = 0;


	if (Hi_Engine::InputHandler::IsKeyHeld(Hi_Engine::eInputType::Key_A) || 
		Hi_Engine::InputHandler::IsKeyPressed(Hi_Engine::eInputType::Key_A))
		m_movement->m_velocity.x = -1;
	else if (Hi_Engine::InputHandler::IsKeyHeld(Hi_Engine::eInputType::Key_D) || 
		Hi_Engine::InputHandler::IsKeyPressed(Hi_Engine::eInputType::Key_D))
		m_movement->m_velocity.x = 1;
	else
		m_movement->m_velocity.x = 0;
}

void C_PlayerController::OnActivate()
{
	m_movement = m_owner->GetComponent<C_Movement>();
}

C_PlayerController* C_PlayerController::Copy() const
{
	auto* res = CU::MemoryPool<C_PlayerController>::GetInstance().GetResource();	// TODO; register in ComponentManager?
	assert(res && "Memory Pool returned invalid memory");

	return new (res) C_PlayerController{ *this };
}