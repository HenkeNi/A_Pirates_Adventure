#pragma once
#include "../Component.h"


// Rename CameraController??
class C_Camera : public Component
{
public:
	C_Camera(GameObject* anOwner);
	~C_Camera();

	void		Init(rapidjson::Value& aValue)			override;
	void		HandleMessage(eCompMessage aMessage)	override;
	void		Update(float aDeltaTime)				override;

	void		OnActivate()							override; 
	void		OnDeactivate()							override;

	C_Camera*	Copy()									override;

private:
	Hi_Engine::Camera m_camera; 
};

