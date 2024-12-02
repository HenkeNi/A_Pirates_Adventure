#pragma once
#include "../../Base/System.h"


class PlayerControllerSystem : public System
{
public:
	PlayerControllerSystem();
	~PlayerControllerSystem();

	void Update(float deltaTime) override;
	void SetSignature() override;

private:
	void GenerateCommands(Entity entity);
};