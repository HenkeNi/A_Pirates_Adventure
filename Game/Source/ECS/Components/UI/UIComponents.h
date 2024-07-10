#pragma once
#include "../Base/Component.h"


/* ######################### UI ######################### */
struct UIComponent : public Component
{
	int RenderDepth = 0; // FIX!
};

struct ButtonComponent : public Component
{
	std::string				Identifier;
	FVector4				HoverColor = { 0.2f, 0.2f, 0.2f, 1.f };

	std::function<void()>	OnClick;
	bool					IsHovered = false; // store button state?? => send mouse click event (ui system listens for it, rather than checking directly if mouse is pressed??)
	bool					IsPressed = false;
	//class Command* Command; // ??
};

struct CursorComponent : public Component
{
};

struct GridComponent : public Component
{
	// FVector2 CellSize;
	IVector2 Dimensions; // grid class? or use inventory.. 
	std::string CellType;
	float SpaceBetweenCells = 0.f; // make FVector2?
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

// TODO; sprite renderer fetches 