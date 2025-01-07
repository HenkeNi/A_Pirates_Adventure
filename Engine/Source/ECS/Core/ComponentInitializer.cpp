#include "Pch.h"
#include "ComponentInitializer.h"
#include "../Components/CoreComponents.h"
#include "Resources/ResourceHolder.h"
#include "Rendering/Texture/Subtexture2D.h"

namespace Hi_Engine
{
	void InitializeComponent(void* component, const ComponentProperties& properties)
	{
	}

	void InitializeComponent(TransformComponent* component, const ComponentProperties& properties)
	{
		component->Position = std::get<FVector2>(properties.at("position"));
		component->Scale = std::get<FVector2>(properties.at("scale"));
		component->Pivot = std::get<FVector2>(properties.at("pivot"));
		component->Rotation = (float)std::get<double>(properties.at("rotation"));
	}

	void InitializeComponent(InputComponent* component, const ComponentProperties& properties)
	{
		component->InputStates.insert({ Hi_Engine::eKey::Key_W, false });
		component->InputStates.insert({ Hi_Engine::eKey::Key_A, false });
		component->InputStates.insert({ Hi_Engine::eKey::Key_S, false });
		component->InputStates.insert({ Hi_Engine::eKey::Key_D, false });
	}

	void InitializeComponent(CameraComponent* component, const ComponentProperties& properties)
	{
	}

	void InitializeComponent(SpriteComponent* component, const ComponentProperties& properties)
	{
		std::string texture = std::get<std::string>(properties.at("texture"));
		IVector2 coordinates = std::get<IVector2>(properties.at("coordinates"));

		component->Subtexture = ResourceHolder<Subtexture2D, SubtextureData>::GetInstance().GetResource({ texture, coordinates.x, coordinates.y });
		component->DefaultColor = component->CurrentColor = std::get<FVector4>(properties.at("color"));
		component->RenderDepth = std::get<int>(properties.at("render_depth"));
	}

	void InitializeComponent(UIComponent* component, const ComponentProperties& properties)
	{
		// component->RenderDepth = std::get<int>(properties.at("render_depth"));
		std::string texture = std::get<std::string>(properties.at("texture"));
		IVector2 coordinates = std::get<IVector2>(properties.at("coordinates"));

		component->Subtexture = ResourceHolder<Subtexture2D, SubtextureData>::GetInstance().GetResource({ texture, coordinates.x, coordinates.y });
		component->DefaultColor = component->CurrentColor = std::get<FVector4>(properties.at("color"));
		component->RenderDepth = std::get<int>(properties.at("render_depth"));
	}

	void InitializeComponent(TimerComponent* component, const ComponentProperties& properties)
	{
		component->Duration = (float)std::get<double>(properties.at("duration"));

		assert(properties.contains("callback") && "No callback registered");

		std::string callbackKey = std::get<std::string>(properties.at("callback"));
		auto itr = CallbackRegistry::Callbacks.find(callbackKey.c_str());

		if (itr != CallbackRegistry::Callbacks.end())
			component->Callback = itr->second;
	}
}