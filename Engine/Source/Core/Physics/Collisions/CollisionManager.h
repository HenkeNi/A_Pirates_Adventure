#pragma once

namespace Hi_Engine
{
	class C_Collider;

	class CollisionManager
	{
	public:
		CollisionManager();
		~CollisionManager();

		void HandleCollisions();
		void AddCollider(C_Collider* aCollider);
		void RemoveCollider(C_Collider* aCollider);

	private:
		void CheckCollisions();
		void ResolveCollision(C_Collider* aCollider1, C_Collider* aCollider2);
		//bool IsColliding(C_Collider* aCollider1, C_Collider* aCollider2);
		//bool IsColliding(C_Collider* aCollider1); -> check with map
		bool Contains(C_Collider* aCollider);

		std::vector<C_Collider*> m_colliders;
	};
}


