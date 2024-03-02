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




/* ######################### HUD ######################### */
struct ItemComponent : public Component // TODO, create a separate file for hud?
{
	std::string Identifier;
	std::string IconTexture;
};

// HERE?? Or maybe use two sprites instead?? add system HealthBarSystem?
struct HealthBarComponent : public Component
{
	Hi_Engine::Material Container;
	Hi_Engine::Material Bar;
	// position? size?
};



// CYRRENTLY IN RENDEIRNG COMPONENTS?!
//struct TextComponent : public ComponentBase
//{
//	class Hi_Engine::Font&	Font;
//	CU::Vector4<float>		Color;
//	std::string				Text;
//	unsigned				Size = 32;
//};