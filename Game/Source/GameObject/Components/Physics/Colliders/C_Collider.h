#pragma once
#include "../../Component.h"
#include "Data/Structs.h"


class CollisionManager;

class C_Collider : public Component
{
public:
	C_Collider(GameObject* anOwner = nullptr);
	virtual ~C_Collider() = default;

	// Draw?? Create a primitive renderer??

	void Activate();
	void Deactivate();

	bool IsActive() const;
	bool IsStatic() const;

	void SetOffset(const CU::Vector3<float>& anOffset);


private:
	friend class CollisionManager;


	  

	CU::Vector3<float>	m_offset;
	bool				m_isActive, m_isStatic;


	// eCollisionLayer?
	CollisionData		m_collisionData;
};

