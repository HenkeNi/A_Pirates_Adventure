#pragma once
#include "../Base/System.h"


class EditorSystem : public System, public Subscriber
{
public:
	EditorSystem();
	~EditorSystem();

	void Receive(Message& message)	override;
	void Update(float deltaTime) override;
	void SetSignature() override;

private:
	void CreateEditorWindows();
};