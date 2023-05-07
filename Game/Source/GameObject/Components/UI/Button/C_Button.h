#pragma once
#include "../../Component.h"

class Command;

// Renaeme UIButton? should listen to Input?? or should Command listen for input?? or Commands in input handler????
class C_Button : public Component
{
public:
	C_Button(GameObject* aGameObject = nullptr);
	~C_Button();

	void Update();
	void SetCommand(Command* aCommand);

private:
	Command* m_command;
};