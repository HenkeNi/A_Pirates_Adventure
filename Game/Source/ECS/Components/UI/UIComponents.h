#pragma once
#include "../Base/Component.h"

struct ButtonComponent : public Component
{
	class Command* Command; // ??
};

struct UIComponent : public Component
{
};

struct HUDComponent : public Component
{
};

// CYRRENTLY IN RENDEIRNG COMPONENTS?!
//struct TextComponent : public ComponentBase
//{
//	class Hi_Engine::Font&	Font;
//	CU::Vector4<float>		Color;
//	std::string				Text;
//	unsigned				Size = 32;
//};