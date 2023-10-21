#pragma once
#include <../GLEW/include/GL/glew.h>
#include <../GLFW/include/GLFW/glfw3.h>
//#include <GL/glew.h>
// #include <GLFW/glfw3.h>

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

	enum class eKey
	{
		Key_Escape	= GLFW_KEY_ESCAPE,
		Key_Enter	= GLFW_KEY_ENTER,
		Key_Tab		= GLFW_KEY_TAB,
		Key_Space	= GLFW_KEY_SPACE,
		Key_LShift	= GLFW_KEY_LEFT_SHIFT,
		Key_0		= GLFW_KEY_0,
		Key_1		= GLFW_KEY_1,
		Key_2		= GLFW_KEY_2,
		Key_3		= GLFW_KEY_3,
		Key_4		= GLFW_KEY_4,
		Key_5		= GLFW_KEY_5,
		Key_6		= GLFW_KEY_6,
		Key_7		= GLFW_KEY_7,
		Key_8		= GLFW_KEY_8,
		Key_9		= GLFW_KEY_9,
		Key_A		= GLFW_KEY_A,
		Key_B		= GLFW_KEY_B,
		Key_C		= GLFW_KEY_C,
		Key_D		= GLFW_KEY_D,
		Key_E		= GLFW_KEY_E,
		Key_F		= GLFW_KEY_F,
		Key_G		= GLFW_KEY_G,
		Key_H		= GLFW_KEY_H,
		Key_I		= GLFW_KEY_I,
		Key_J		= GLFW_KEY_J,
		Key_K		= GLFW_KEY_K,
		Key_L		= GLFW_KEY_L,
		Key_M		= GLFW_KEY_M,
		Key_N		= GLFW_KEY_N,
		Key_O		= GLFW_KEY_O,
		Key_P		= GLFW_KEY_P,
		Key_Q		= GLFW_KEY_Q,
		Key_R		= GLFW_KEY_R,
		Key_S		= GLFW_KEY_S,
		Key_T		= GLFW_KEY_T,
		Key_U		= GLFW_KEY_U,
		Key_V		= GLFW_KEY_V,
		Key_W		= GLFW_KEY_W,
		Key_X		= GLFW_KEY_X,
		Key_Y		= GLFW_KEY_Y,
		Key_Z		= GLFW_KEY_Z,
		Key_Up		= GLFW_KEY_UP,
		Key_Down	= GLFW_KEY_DOWN,
		Key_Left	= GLFW_KEY_LEFT,
		Key_Right	= GLFW_KEY_RIGHT
	};

	enum class eMouseBtn
	{
		LeftBtn		= GLFW_MOUSE_BUTTON_LEFT,
		RightBtn	= GLFW_MOUSE_BUTTON_RIGHT,
		MouseWheel  = GLFW_MOUSE_BUTTON_MIDDLE
	};

	enum class eInputState
	{
		Press		= GLFW_PRESS, 
		Release		= GLFW_RELEASE, 
		Repeat		= GLFW_REPEAT
	};


	//enum class eInputType
	//{
	//	Key_Enter   = GLFW_KEY_ENTER,
	//	Key_Space	= GLFW_KEY_SPACE,
	//	Key_Escape	= GLFW_KEY_ESCAPE,
	//	Key_Shift   = GLFW_KEY_LEFT_SHIFT,
	//	Key_W,
	//	Key_A,
	//	Key_S,
	//	Key_D,
	//	Key_P,
	//	Key_ArrowUp,
	//	Key_ArrowDown,
	//	Key_ArrowLeft,
	//	Key_ArrowRight,
	//	Mouse_LeftBtn,
	//	Mouse_RightBtn,
	//	// Mouse_Moved,
	//	Count
	//};

	

	enum class eCameraMovement
	{
		Forward, Backward, Left, Right
	};

	enum class eTextAlginment
	{
		Align_Left,
		Align_Center,
		Align_Right,
		Align_Top,
		Align_Bottom,
	};

	enum class eRenderCommandType
	{
		SetShader,
		SetCamera,
		DrawSprite
	};
}