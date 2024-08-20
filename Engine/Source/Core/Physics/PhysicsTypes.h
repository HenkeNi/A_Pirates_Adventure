#pragma once

class b2Body;

namespace Hi_Engine
{
	struct PhysicsSettings
	{

	};


	class PhysicsBody
	{
	public:
		PhysicsBody(b2Body* body = nullptr);

		void SetBody(b2Body* body);
		void SetVelocity(const FVector2& velocity);

		void ApplyForce(const FVector2& force);

		FVector2 GetPosition() const;

	private:
		b2Body* m_body;
		
	};

	//struct BoxCollider // make class?
	//{
	//	b2Body* Body;
	//};

	struct StaticColliderData
	{
		FVector2 Position;
		FVector2 Size;
	};

	struct DynamicColliderData
	{
		FVector2 Position;
		FVector2 Size;
		float Density = 1.f;
		float Friction = 0.3f;
	};
}
