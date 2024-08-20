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
	void UpdateButtons(const FVector2& cursorPosition);
	FVector2 GetCurrentMousePosition() const;

	// void AssignCallback(Entity* button);

	void OnButtonActivated(Entity button);
	void AllignBoundingBox(Entity entity);
};