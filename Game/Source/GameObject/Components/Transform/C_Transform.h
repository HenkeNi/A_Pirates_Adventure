#pragma once
#include "../Component.h"

namespace CU = CommonUtilities;

// TODO: Make C_Sprite a firend class??

class C_Transform : public Component
{
public:
	C_Transform(GameObject* anOwner);
	~C_Transform();

	void						Init(rapidjson::Value& aValue)								override;
	void						HandleMessage(eMessageType aType, const std::any& someData)	override;
	void						Update(float aDeltaTime)									override;
	void						LateUpdate(float aDeltaTime)								override;
	C_Transform*				Copy()														override;

	void						SetPosition(const CU::Vector2<float>& aPosition);
	void						SetPosition(float aX, float aY);
	void						SetXPosition(float aX);
	void						SetYPosition(float aY);
	void						SetScale(const CU::Vector2<float>& aScale);
	void						SetRotation(float aRotation);

	void						MoveBy(const CU::Vector2<float>& aOffset);
	void						MoveBy(float anOffsetX, float anOffsetY);

	const CU::Vector2<float>&	GetPosition()												   const;
	const CU::Vector2<float>&	GetScale()													   const;
	float						GetRotation()												   const;
	bool						HasMoved()													   const;

private:
	CU::Vector2<float>			m_currPosition, m_prevPosition;
	CU::Vector2<float>			m_scale; 
	float						m_rotation;
};