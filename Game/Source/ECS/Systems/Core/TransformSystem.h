#pragma once
#include "../Base/System.h"

class TransformSystem : public System
{
public:
	TransformSystem();
	~TransformSystem();

	void Receive(Message& message)	override;
	void Update(float deltaTime)	override;

private:

};