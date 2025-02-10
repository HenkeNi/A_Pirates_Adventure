#pragma once
#include "../Utility/ECSTypes.h"

// Store in core components file? Pass in entity?

namespace Hi_Engine
{
	void InitializeComponent(void* component, const ComponentProperties& properties);

	void InitializeComponent(struct TransformComponent* component, const ComponentProperties& properties);

	void InitializeComponent(struct InputComponent* component, const ComponentProperties& properties);

	void InitializeComponent(struct CameraComponent* component, const ComponentProperties& properties);

	void InitializeComponent(struct SpriteComponent* component, const ComponentProperties& properties);

	void InitializeComponent(struct UIComponent* component, const ComponentProperties& properties);

	void InitializeComponent(struct TimerComponent* component, const ComponentProperties& properties);
}
