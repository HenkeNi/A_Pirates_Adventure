#pragma once
#include "../Core/Modules/Module.h"
#include "PhysicsTypes.h"

class b2World;

namespace Hi_Engine
{
	class Physics : public Module
	{
	public:
		Physics(ModuleManager& manager);
		~Physics();

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

		
	private:
		FVector2 m_gravity;
		b2World* m_world;

		// store settings...


	//	PhysicsSystem;
	//	MovementSystem;
	};
}