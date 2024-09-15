#pragma once


/* ######################### UI ######################### */
struct UIComponent
{
	//int RenderDepth = 0; // FIX!
};

struct ButtonComponent
{
	enum class eButtonState
	{
		Idle,
		Hovered,
		Clicked,
		Released,
		Disabled
	} CurrentState;

	std::string				Identifier;

	FVector4				HoverColor = { 0.2f, 0.2f, 0.2f, 1.f };

	std::function<void()>	OnClick; // or a Command?
	//bool					IsHovered = false; // store button state?? => send mouse click event (ui system listens for it, rather than checking directly if mouse is pressed??)
	//bool					IsPressed = false;
};

struct CursorComponent
{
};

struct GridComponent
{
	// FVector2 CellSize;
	IVector2 Dimensions; // grid class? or use inventory.. 
	std::string CellType;
	float SpaceBetweenCells = 0.f; // make FVector2?
};

/* ######################### HUD ######################### */
struct HUDComponent
{
};

struct ItemComponent // TODO, create a separate file for hud?
{
	std::string Identifier;
	std::string IconTexture;
};

// HERE?? Or maybe use two sprites instead?? add system HealthBarSystem?
struct HealthBarComponent
{
	Hi_Engine::Material Container;
	Hi_Engine::Material Bar;
	// position? size?
};

struct CrosshairComponent
{
	// target? position?
};


/* ######################### Inventory ######################### */

// TODO; sprite renderer fetches 