#pragma once
#include "../../Component.h"
#include "Data/Structs.h"

//class Hi_Engine::CollisionManager;
namespace Hi_Engine
{
	class CollisionManager;
}

class C_Collider : public Component
{
public:
	C_Collider(GameObject* anOwner = nullptr);


	bool IsActivated() const;

private:
	friend class CollisionManager;

	// eCollisionLayer?
	CollisionData		m_collisionData;
	CU::Vector3<float>	m_offset;
	bool				m_isActive;
};

