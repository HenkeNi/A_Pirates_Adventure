#pragma once

namespace Hi_Engine
{
	struct ImGuiButton
	{
		std::function<void()> Callback;
		const char* Label;
	};

	struct ImGuiCombo
	{
		constexpr static unsigned MaxItems = 5;
		const char* Items[MaxItems];
		const char* Label;
		int ItemAmoun;
		int CurrentItem;
	};

	struct ImGuiSlider
	{
		float Value;
		float MinValue;
		float MaxValue;
		const char* Label;
	};

	struct ImGuiWindow
	{
		std::vector<ImGuiButton> Buttons;
		FVector2				 Position;
		FVector2				 Size;
		const char*				 Title;
		bool					 IsMovable;
		bool					 IsResizable;
	};
}