#pragma once
#include "../Base/System.h"

class UISystem : public System
{
public:
	UISystem();
	~UISystem();

	void Receive(Message& aMsg)		override;
	void Update(float aDeltaTime)	override;

	static glm::vec2 ScreenToWorldCoordinates(const glm::vec2& aPosition);

private:
	void OnButtonActivated(Entity* aButton);
};