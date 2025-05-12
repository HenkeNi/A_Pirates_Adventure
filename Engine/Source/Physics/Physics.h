#pragma once
#include "../Services/IService.h"
#include "PhysicsTypes.h"

class b2World;

namespace Hi_Engine
{
	// Handle physics differently? maybe not a service? maybe each scene or world?
	class Physics : public IService
	{
	public:
		Physics();
		~Physics();

		bool Initialize()							  override;
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