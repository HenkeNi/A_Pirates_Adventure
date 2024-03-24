#pragma once
#include "../Base/System.h"

class UISystem : public System
{
public:
	UISystem();
	~UISystem();

	void Receive(Message& message)	override;
	void Update(float deltaTime)	override;

	static glm::vec2 ScreenToWorldCoordinates(const glm::vec2& position);

private:
	void OnButtonActivated(Entity* button);
	//void AssignCallback(Entity* button);
	void UpdateCursor();
};