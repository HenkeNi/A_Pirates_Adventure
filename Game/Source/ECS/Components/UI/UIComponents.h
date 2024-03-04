#pragma once
#include "../Base/Component.h"

struct ButtonComponent : public Component
{
	std::function<void()> OnClick;
	//class Command* Command; // ??
};

struct UIComponent : public Component
{
};





/* ######################### HUD ######################### */
struct HUDComponent : public Component
{
};

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



struct CursorComponent : public Component
{

};

struct CrosshairComponent : public Component
{
	// target?
};

// CYRRENTLY IN RENDEIRNG COMPONENTS?!
//struct TextComponent : public ComponentBase
//{
//	class Hi_Engine::Font&	Font;
//	CU::Vector4<float>		Color;
//	std::string				Text;
//	unsigned				Size = 32;
//};