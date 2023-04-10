#pragma once

namespace Hi_Engine
{
	enum class ePriority
	{
		Low, Moderate, High, NotSpecified
	};

	enum class eWindowEvent
	{
		None, Resize, LostFocus, GainedFocus, Close
	};

	enum class eInputType
	{
		Key_Enter,
		Key_Space,
		Key_Escape,
		Key_W,
		Key_A,
		Key_S,
		Key_D,
		Key_P,
		Key_ArrowUp,
		Key_ArrowDown,
		Key_ArrowLeft,
		Key_ArrowRight,
		Mouse_LeftBtn,
		Mouse_RightBtn,
		Mouse_Moved,
		Count
	};

	enum class eInputState
	{
		None, Press, Release, Repeat
	};

	enum class eCameraMovement
	{
		Forward, Backward, Left, Right
	};
}