#pragma once
#include "../../Component.h"

namespace CU = CommonUtilities;

class C_PlayerController;
class C_Transform;


// Take in direction instead?? don't forget to normalzie...

// Make C_player controller a friend class?? maybe enemy controller as well?? - or to many??
class C_Movement : public Component
{
public:
	C_Movement(GameObject* anOwner = nullptr);

	void		Init(rapidjson::Value& aValue)				override;
	void		HandleMessage(const CompMessage& aMsg)	override;
	void		Update(float aDeltaTime)					override;
	void		LateUpdate(float aDeltaTime)				override;
	void		OnActivate()								override;
	C_Movement* Copy()								  const override;

private:
	friend class C_PlayerController;

	CU::Vector3<float>	m_velocity;				// vec2 or 3??
	float				m_movementSpeed;
	C_Transform*		m_transform;

	// Curr velocity, prev velocity, max velocity,
	// curr speed, max speed?! (prevSpeed??


	//	m_acceleration;
	//CU::Vector2<float>	m_velocity,		m_acceleration;
	//CU::Vector2<float>	m_maxVelocity,	m_maxAcceleration;
};