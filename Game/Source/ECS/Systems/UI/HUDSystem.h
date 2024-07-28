#pragma once
#include "../Base/System.h"


class HUDSystem : public System, public Subscriber
{
public:
	HUDSystem();
	~HUDSystem();

	void Receive(Message& message)	override;
	void Update(float deltaTime)	override;
	void SetSignature()				override;

	// Handle rendering as well?

private:
	void SetupHUDElements(); // maybe should be done dynamically (at runtime) rather than at game start?
	void UpdateHealthDisplay(Entity entity);
	void UpdateInventoryBar();
};