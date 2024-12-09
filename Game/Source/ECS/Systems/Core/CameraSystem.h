#pragma once
#include "../Base/System.h"


using CameraBounds = Hi_Engine::Geometry::AABB2D<float>;

/* TODO; make sure to update after movement... */
class CameraSystem : public System, public Subscriber
{
public:
	CameraSystem();
	~CameraSystem();

	void Receive(Message& message)	override;
	void Update(float deltaTime)	override;

	void SetSignature() override;

private:
	void CullEntities(const CameraBounds& bounds); // combine? check all entiteis with bounding box?
	void CullMapChunks(const CameraBounds& bounds);
};