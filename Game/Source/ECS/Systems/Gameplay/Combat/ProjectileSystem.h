#pragma once
#include "../../Base/System.h"


class ProjectileSystem : public System, public Subscriber
{
public:
	ProjectileSystem();
	~ProjectileSystem();

	void Receive(Message& message)	override;
	void Update(float deltaTime)	override;
	void SetSignature()				override;
};