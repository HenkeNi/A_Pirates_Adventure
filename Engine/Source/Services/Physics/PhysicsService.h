#pragma once
#include "../IService.h"
#include "PhysicsTypes.h"
#include "Source/Core/Math/Vectors/Vector.hpp" // remoev

class b2World;

namespace Hi_Engine
{
	// Handle physics differently? maybe not a service? maybe each scene or world?
	class PhysicsService : public IService
	{
	public:
		PhysicsService();
		~PhysicsService();

		bool Initialize();
		void Shutdown() override;
		void Deserialize(const char* path);

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