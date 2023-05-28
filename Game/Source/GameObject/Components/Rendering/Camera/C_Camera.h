#pragma once
#include "../../Component.h"

// TODO; functon for activateCamera?? deactivates the other cameras???

namespace CU = CommonUtilities;

// Rename CameraController?? or add a CameraController component??
class C_Camera : public Component
{
public:
	C_Camera(GameObject* anOwner = nullptr);
	~C_Camera();

	void		Init(rapidjson::Value& aValue)			override;
	void		HandleMessage(const CompMessage& aMsg)		override; // TODO; move camera when	updating position...
	void		Update(float aDeltaTime)				override;	

	void		OnActivate()							override; 
	void		OnDeactivate()							override;

	C_Camera*	Copy()							  const override;

	void		SetTarget(GameObject* aTarget);

private:
	//Hi_Engine::OrthographicCamera m_camera;   use pointer!
	Hi_Engine::Camera	m_camera; 
	GameObject*			m_target; 		// use look at??
	CU::Vector3<float>	m_targetOffset;

	// field of view, near, far clip planes??


	// bool m_isMainCamera;
	// Add offset? vec3..
};

