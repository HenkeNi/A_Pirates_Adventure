#include "Pch.h"
#include "PhysicsService.h"
#include <box2d/box2d.h>

namespace Hi_Engine
{
	PhysicsService::PhysicsService()
		: m_gravity{ 0.f, 0.f }, m_world{ nullptr }
	{
	}

	PhysicsService::~PhysicsService()
	{
		delete m_world;
	}

	bool PhysicsService::Initialize()
	{
		m_world = new b2World{{ m_gravity.x, m_gravity.y }};

		return true;
	}

	void PhysicsService::Shutdown() noexcept
	{
	}

	void PhysicsService::Deserialize(const char* path)
	{
	}

	void PhysicsService::Update(float deltaTime)
	{
		static const float timeStep = 1.f / 60.f;
		static const int velocityIterations = 6;
		static const int positionIterations = 3;

		if (m_world)
		{
			m_world->Step(timeStep, velocityIterations, positionIterations);
		}
	}

	//void Physics::DebugDraw()
	//{
	//	m_world->SetDebugDraw();
	//	m_world->DebugDraw();
	//}

	void PhysicsService::SetGravity(const FVector2& gravity)
	{
		m_world->SetGravity({ gravity.x, gravity.y });
	}

	PhysicsBody PhysicsService::CreateDynamicBody(const DynamicColliderData& data)
	{
		const auto& [position, size, density, friction] = data;

		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(position.x, position.y);
		b2Body* body = m_world->CreateBody(&bodyDef);

		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(size.x, size.y);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;
		fixtureDef.density = 0.25f;
		fixtureDef.friction = friction;

		body->CreateFixture(&fixtureDef);

		return PhysicsBody{ body };
	}

	PhysicsBody PhysicsService::CreateStaticBody(const StaticColliderData& data)
	{
		const auto& [position, size] = data;

		b2BodyDef bodyDef;
		bodyDef.type = b2_staticBody;
		bodyDef.position.Set(position.x, position.y);
		b2Body* body = m_world->CreateBody(&bodyDef);

		b2PolygonShape staticBox;
		staticBox.SetAsBox(size.x, size.y);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &staticBox;

		body->CreateFixture(&fixtureDef);

		return PhysicsBody{ body };
	}

	void PhysicsService::DestroyBody(PhysicsBody& body)
	{
		m_world->DestroyBody(body.m_body);
		body.m_body = nullptr;
	}
}