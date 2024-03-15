#pragma once
#include "../Base/Component.h"


/* ######################### UI ######################### */
struct UIComponent : public Component
{
};

struct ButtonComponent : public Component
{
	std::function<void()>	OnClick;
	bool					IsHovered; // store button state?? => send mouse click event (ui system listens for it, rather than checking directly if mouse is pressed??)
	CU::Vector4<float>		HoverColor = { 0.2f, 0.2f, 0.2f, 1.f }; // HERE??
	//class Command* Command; // ??
};

struct CursorComponent : public Component
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

struct CrosshairComponent : public Component
{
	// target? position?
};


/* ######################### Inventory ######################### */
struct GridComponent : public Component
{
	CU::Vector2<unsigned> Grid; // grid class? or use inventory..
};

// TODO; sprite renderer fetches 