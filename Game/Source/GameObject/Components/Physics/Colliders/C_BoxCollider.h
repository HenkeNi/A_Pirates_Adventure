#pragma once 
#include "C_Collider.h"


namespace
{
	using AABB = Hi_Engine::Physics::AABB2D<float>;
}

class C_BoxCollider : public C_Collider
{
public:
	C_BoxCollider(GameObject* anOwner = nullptr);
	~C_BoxCollider();

	void				Init(rapidjson::Value& aValue)					override;
	void				HandleMessage(const CompMessage& aMsg)			override;
	void				Update(float aDeltaTime)						override;
	void				LateUpdate(float aDeltaTime)					override;
	void				Draw()									  const override;
	C_BoxCollider*		Copy()									  const override;

private:
	AABB				m_aabb;
};
