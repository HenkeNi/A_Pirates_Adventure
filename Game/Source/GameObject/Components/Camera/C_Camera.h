#pragma once
#include "../Component.h"


// Rename CameraController??
class C_Camera : public Component
{
public:
	C_Camera(GameObject* anOwner = nullptr);
	~C_Camera();

	void		Init(rapidjson::Value& aValue)			override;
	void		HandleMessage(CompMessage aMessage)		override; // TODO; move camera when	updating position...
	void		Update(float aDeltaTime)				override;	

	void		OnActivate()							override; 
	void		OnDeactivate()							override;

	C_Camera*	Copy()							  const override;

private:
	Hi_Engine::Camera m_camera; 
};

