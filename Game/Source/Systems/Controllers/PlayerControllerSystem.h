#pragma once
#include "Base/System.h"

class PlayerControllerSystem : public System
{
public:
	PlayerControllerSystem();
	~PlayerControllerSystem();

	void Receive(Message& aMsg)		override;
	void Update(float aDeltaTime)	override;

private:
	// TODO; replace with playercontroller component => (Commands??)
	// std::unordered_map<Hi_Engine::eInputType, 

	void InitCommands();
};