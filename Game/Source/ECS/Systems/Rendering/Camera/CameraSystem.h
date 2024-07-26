#pragma once
#include "../../Base/System.h"


/* TODO; make sure to update after movement... */
class CameraSystem : public System, public Subscriber
{
public:
	CameraSystem();
	~CameraSystem();

	void Receive(Message& message)	override;
	void Update(float deltaTime)	override;

	void SetSignature() override;


	// static std::vector<Entity*> GetEntitiesInView(std::vector<Entity*> someEntities);
	// static bool IsEntityInView() const;

	//static bool IsInView(Entity camera, const Hi_Engine::Physics::AABB2D<float>& bounds); // Rename: Is visible?

private:

	// TODO: CameraSystem does fustrum culling?!
	void CullEntities();

	//bool IsVisible(Entity* entity) const; // rename
};