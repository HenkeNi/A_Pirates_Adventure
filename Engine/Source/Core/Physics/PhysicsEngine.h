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

		PhysicsBody CreateDynamicBody(const DynamicColliderData& data);
		PhysicsBody CreateStaticBody(const StaticColliderData& data);

		// destroy?



	private:
		FVector2 m_gravity;
		b2World* m_world;

		// store settings...
	};
}