#pragma once
#include "Base/System.h"

/* TODO; make sure to update after movement... */
class CameraSystem : public System
{
public:
	CameraSystem();
	~CameraSystem();

	void Receive(Message& aMsg)		override;
	void Update(float aDeltaTime)	override;

private:


};

