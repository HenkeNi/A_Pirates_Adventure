#pragma once
#include "../Base/System.h"


class HUDSystem : public System, public Subscriber
{
public:
	HUDSystem();
	~HUDSystem();

	void Receive(Message& message)	override;
	void SetSignature()				override;

private:
	void SetupHUDElements(); // maybe should be done dynamically (at runtime) rather than at game start?
	void UpdateCursorTexture(Entity entity, bool isAiming);

	void UpdateHealthDisplay(Entity entity);
	void UpdateInventoryBar();
};