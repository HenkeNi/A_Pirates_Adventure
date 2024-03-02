#pragma once
#include "../Base/System.h"

class TransformSystem : public System
{
public:
	TransformSystem();
	~TransformSystem();

	void Receive(Message& aMsg)		override;
	void Update(float aDeltaTime)	override;

private:

};