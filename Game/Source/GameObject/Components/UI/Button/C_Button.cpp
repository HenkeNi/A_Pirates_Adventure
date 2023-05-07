#include "Pch.h"
#include "C_Button.h"

C_Button::C_Button(GameObject* aGameObject)
	: Component{ aGameObject }, m_command{ nullptr }
{
}

C_Button::~C_Button()
{}

void C_Button::Update()
{
	// Check for button press??
}

void C_Button::SetCommand(Command* aCommand)
{
	delete m_command;
	m_command = aCommand;
}