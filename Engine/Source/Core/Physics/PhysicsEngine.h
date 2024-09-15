#pragma once
#include "../Modules/Base/Module.h"
#include "PhysicsTypes.h"

class b2World;

namespace Hi_Engine
{
	class PhysicsEngine : public Module
	{
	public:
		PhysicsEngine(int initOrder);
		~PhysicsEngine();

		bool Init()									  override;
		void Shutdown()								  override;
		void Deserialize(const rapidjson::Value& json) override;

		void Update(float deltaTime);
		//void DebugDraw();

		void SetGravity(const FVector2& gravity);

		PhysicsBody CreateDynamicBody(const DynamicColliderData& data);
		PhysicsBody CreateStaticBody(const StaticColliderData& data);

		void DestroyBody(PhysicsBody& body);

		// destroy?

		void Test();

	private:
		FVector2 m_gravity;
		b2World* m_world;

		// store settings...
	};
}