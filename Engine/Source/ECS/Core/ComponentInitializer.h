#pragma once
#include "../Utility/ECSTypes.h"

// Store in core components file? Pass in entity?

namespace Hi_Engine
{
	void InitializeComponent(void* component, const ComponentProperties& properties);

	void InitializeComponent(class TransformComponent* component, const ComponentProperties& properties);

	void InitializeComponent(class InputComponent* component, const ComponentProperties& properties);

	void InitializeComponent(class CameraComponent* component, const ComponentProperties& properties);

	void InitializeComponent(class SpriteComponent* component, const ComponentProperties& properties);

	void InitializeComponent(class UIComponent* component, const ComponentProperties& properties);

	void InitializeComponent(class TimerComponent* component, const ComponentProperties& properties);
}
