#pragma once
#include "../Base/System.h"


class AudioSystem : public System, public Subscriber
{
public:
	AudioSystem();
	~AudioSystem();

	void Receive(Message& message)	override;
	void Update(float deltaTime)	override;
	void SetSignature()				override;
};