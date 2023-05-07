#pragma once
#include "../Component.h"

namespace CU = CommonUtilities;

// TODO: Make C_Sprite a firend class??
// Make C_Movement a friend class?? and remove setters?!
class C_Transform : public Component
{
public:
	C_Transform(GameObject* anOwner = nullptr);
	~C_Transform();

	void						Init(rapidjson::Value& aValue)						 override;
	void						HandleMessage(CompMessage aMessage)					 override;
	void						Update(float aDeltaTime)							 override;
	void						LateUpdate(float aDeltaTime)						 override;
	C_Transform*				Copy()										   const override;

	void						SetPosition(const CU::Vector3<float>& aPosition);					// replace functions with friend classes instead??
	void						SetPosition(float aX, float aY, float aZ);
	void						SetXPosition(float aX);
	void						SetYPosition(float aY);
	void						SetZPosition(float aZ);
	void						SetScale(const CU::Vector3<float>& aScale);
	void						SetRotation(float aRotation);

	void						MoveBy(const CU::Vector3<float>& anOffset);
	void						MoveBy(float anOffsetX, float anOffsetY, float anOffsetZ);

	const CU::Vector3<float>&	GetPosition()											const;
	const CU::Vector3<float>&	GetScale()												const;
	float						GetRotation()											const;
	bool						HasMoved()												const;

private:
	CU::Vector3<float>			m_currPosition, m_prevPosition;
	CU::Vector3<float>			m_scale; 
	float						m_rotation;
};