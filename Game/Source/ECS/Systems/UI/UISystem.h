#pragma once
#include "../Base/System.h"


class UISystem : public System, public Subscriber
{
public:
	UISystem();
	~UISystem();

	void Receive(Message& message)	override;
	void Update(float deltaTime)	override;
	void SetSignature()				override;

private:
	void OnButtonActivated(Entity button);
	//void AssignCallback(Entity* button);
	void UpdateCursor();
};