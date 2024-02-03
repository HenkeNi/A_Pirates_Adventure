#pragma once
#include "../Base/System.h"


class HUDSystem : public System
{
public:
	HUDSystem();
	~HUDSystem();

	void Receive(Message& aMsg)		override;
	void Update(float aDeltaTime)	override;

	// Handle rendering as well?

private:
	void SetupHUDElements(); // maybe should be done dynamically (at runtime) rather than at game start?
	void UpdateCursor();

};