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

			m_body->SetAwake(true);
			m_body->SetLinearVelocity({ velocity.x, velocity.y });
		}
	}

	void PhysicsBody::ApplyForce(const FVector2& force)
	{
		if (m_body)
		{

			assert(m_body->GetType() == b2BodyType::b2_dynamicBody && "ERROR");
			m_body->ApplyForce({ force.x, force.y }, m_body->GetWorldCenter(), true);
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
	FVector2 PhysicsBody::GetSize() const
	{
		FVector2 size{ 0.f, 0.f };

		if (m_body)
		{
			b2PolygonShape* boxShape = (b2PolygonShape*)m_body->GetFixtureList()->GetShape();
			b2Vec2 halfExtents = boxShape->m_vertices[1];

			size.x = halfExtents.x * 2.f;
			size.y = halfExtents.y * 2.f;
		}


		return size;
	}
}