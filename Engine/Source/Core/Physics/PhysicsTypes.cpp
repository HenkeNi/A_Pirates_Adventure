#include "Pch.h"
#include "PhysicsTypes.h"
#include "box2d/box2d.h"


namespace Hi_Engine
{
	PhysicsBody::PhysicsBody(b2Body* body)
		: m_body{ body }
	{
	}


	void PhysicsBody::SetBody(b2Body* body)
	{
		m_body = body;
	}

	void PhysicsBody::SetVelocity(const FVector2& velocity)
	{
		if (m_body)
		{
			assert(m_body->IsEnabled() && "TEST");
			assert(m_body->GetType() == b2BodyType::b2_dynamicBody && "ERROR");

			// std::cout << "VEL: " << velocity.x << "; " << velocity.y << "\n";
			m_body->SetLinearVelocity({ velocity.x * 100.f, velocity.y * 100.f });
			m_body->SetAwake(true);
		}
	}

	FVector2 PhysicsBody::GetPosition() const // pass optional?
	{
		FVector2 position{ 0.f, 0.f };

		if (m_body)
		{
			auto bodyPosition = m_body->GetPosition();
			position = { bodyPosition.x, bodyPosition.y };
		}

		return position;
	}
}