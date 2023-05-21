#pragma once
#include "../../Component.h"

class C_Movement;

// Base class AI_Controller??

// use commands instead of subscribing to input?? or use observer pattern for input instead??
class C_PlayerController : public Component, public Hi_Engine::EventListener 
{
public:
	C_PlayerController(GameObject* anOwner = nullptr);

	void				Init(rapidjson::Value& aValue)				override;
	void				HandleMessage(const CompMessage& aMsg)		override;
	void				HandleEvent(Hi_Engine::KeyEvent& anEvent)   override;
	void				Update(float aDeltaTime)					override;
	void				OnActivate()								override;
	C_PlayerController* Copy()								  const override;



private:
	C_Movement* m_movement;
};

