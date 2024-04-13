#pragma once
#include "../Base/System.h"

class AudioSystem : public System
{
public:
	AudioSystem();
	~AudioSystem();

	void Receive(Message& message)	override;
	void Update(float deltaTime)	override;
private:

};

