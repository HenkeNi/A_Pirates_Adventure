#pragma once
#include "../Base/System.h"

// Integrate into combat system? together with knockbacks? or have callback on attack?
class ShakeSystem : public System, public Subscriber
{
public:
	ShakeSystem();
	~ShakeSystem();

	void Receive(Message& message)	override;
	void Update(float deltaTime)	override;
	void SetSignature()				override;

};