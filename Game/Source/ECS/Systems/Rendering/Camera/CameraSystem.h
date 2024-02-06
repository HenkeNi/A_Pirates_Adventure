#pragma once
#include "../../Base/System.h"

class Entity;

/* TODO; make sure to update after movement... */
class CameraSystem : public System
{
public:
	CameraSystem();
	~CameraSystem();

	void Receive(Message& aMsg)		override;
	void Update(float aDeltaTime)	override;

	// static std::vector<Entity*> GetEntitiesInView(std::vector<Entity*> someEntities);
	// static bool IsEntityInView() const;

	static bool IsInView(Entity* aCamera, const Hi_Engine::Physics::AABB2D<float>& someBounds); // Rename: Is visible?

private:
	// TODO: CameraSystem does fustrum culling?!
	void CullEntities();
	bool IsVisible(class Entity* anEntity) const; // rename
};