#pragma once
//#include <../ThirdParty/GLEW/include/GL/glew.h>

//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include <../ThirdParty/GLEW/include/GL/glew.h>
//#include <../ThirdParty/GLFW/include/GLFW/glfw3.h>
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
// #include <../../ThirdParty/../GLFW/include/GLFW/glfw3.h>
//#include <../../ThirdParty/GLEW/include/GL/glew.h>
//#include <../GLEW/include/GL/glew.h>
//#include <../GLFW/include/GLFW/glfw3.h>
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
		Key_Space	= 32,  //	GLFW_KEY_SPACE,
		Key_0		= 48,  //	GLFW_KEY_0,
		Key_1		= 49,  //	GLFW_KEY_1,
		Key_2		= 50,  //	GLFW_KEY_2,
		Key_3		= 51,  //	GLFW_KEY_3,
		Key_4		= 52,  //	GLFW_KEY_4,
		Key_5		= 53,  //	GLFW_KEY_5,
		Key_6		= 54,  //	GLFW_KEY_6,
		Key_7		= 55,  //	GLFW_KEY_7,
		Key_8		= 56,  //	GLFW_KEY_8,
		Key_9		= 57,  //	GLFW_KEY_9,
		Key_A		= 65,  //	GLFW_KEY_A,
		Key_B		= 66,  //	GLFW_KEY_B,
		Key_C		= 67,  //	GLFW_KEY_C,
		Key_D		= 68,  //	GLFW_KEY_D,
		Key_E		= 69,  //	GLFW_KEY_E,
		Key_F		= 70,  //	GLFW_KEY_F,
		Key_G		= 71,  //	GLFW_KEY_G,
		Key_H		= 72,  //	GLFW_KEY_H,
		Key_I		= 73,  //	GLFW_KEY_I,
		Key_J		= 74,  //	GLFW_KEY_J,
		Key_K		= 75,  //	GLFW_KEY_K,
		Key_L		= 76,  //	GLFW_KEY_L,
		Key_M		= 77,  //	GLFW_KEY_M,
		Key_N		= 78,  //	GLFW_KEY_N,
		Key_O		= 79,  //	GLFW_KEY_O,
		Key_P		= 80,  //	GLFW_KEY_P,
		Key_Q		= 81,  //	GLFW_KEY_Q,
		Key_R		= 82,  //	GLFW_KEY_R,
		Key_S		= 83,  //	GLFW_KEY_S,
		Key_T		= 84,  //	GLFW_KEY_T,
		Key_U		= 85,  //	GLFW_KEY_U,
		Key_V		= 86,  //	GLFW_KEY_V,
		Key_W		= 87,  //	GLFW_KEY_W,
		Key_X		= 88,  //	GLFW_KEY_X,
		Key_Y		= 89,  //	GLFW_KEY_Y,
		Key_Z		= 90,  //   GLFW_KEY_Z,
		Key_Escape	= 256, //	GLFW_KEY_ESCAPE,
		Key_Enter	= 257, //	GLFW_KEY_ENTER,
		Key_Tab		= 258, //	GLFW_KEY_TAB,
		Key_Right	= 262, //	GLFW_KEY_RIGHT
		Key_Left	= 263, //	GLFW_KEY_LEFT,
		Key_Down	= 264, //	GLFW_KEY_DOWN,
		Key_Up		= 265, //	GLFW_KEY_UP,
		Key_LShift	= 340, //	GLFW_KEY_LEFT_SHIFT,
	};

	enum class eMouseBtn
	{
		LeftBtn		= 0,   //	GLFW_MOUSE_BUTTON_LEFT,
		RightBtn	= 1,   //	GLFW_MOUSE_BUTTON_RIGHT,
		MouseWheel  = 2,   //	GLFW_MOUSE_BUTTON_MIDDLE
	};

	enum class eInputState
	{
		Press		= 1,   //	GLFW_PRESS, 
		Release		= 0,   //	GLFW_RELEASE, 
		Repeat		= 2,   //	GLFW_REPEAT,
		Invalid		= -1
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
		SetProjectionMatrix,
		DrawSprite,
		DrawBatch,
	};
}