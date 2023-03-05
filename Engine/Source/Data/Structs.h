#pragma once
#include "../Utility/Math/Vectors/Vector.hpp"
#include <functional>

namespace CU = CommonUtilities;

namespace Hi_Engine
{
	struct WindowData
	{
		CU::Vector2<unsigned>	m_size;
		std::string				m_name, m_iconPath;
	};

	struct CameraData
	{
		CU::Vector3<float>	m_position;
		CU::Vector3<float>	m_front, m_up, m_right; // make struct for coordinate system?
		CU::Vector3<float>	m_worldUp;

		float				m_movmentSpeed, m_zoom;
	};



	class Texture2D;
	
	struct SpriteRenderData
	{
		Texture2D&			m_texture;
		CU::Vector4<float>	m_color;
		CU::Vector3<float>	m_position;
		CU::Vector2<float>	m_size;			// Rename Scale??
		float				m_rotation;
	};


	// Put in Game??
	class InputHandler;
	class Window;

	struct SharedContext
	{
		// SceneManagerProxy	m_sceneManager;
		// Window&				m_window;
		InputHandler& m_inputHandler; // Pass around?? Or do everytihng with events??
		// Timer& m_timer; // ?? or a proxy??
	};







	//class TimeObserver; // RENAME??

	struct TimerRequest // RENAME??
	{
		double					m_durationInSecs, m_timeOfRequest;
		std::function<void()>	m_callback = nullptr;

		//TimeObserver*			m_observer = nullptr;
	};








	//??
	//struct Position
	//{
	//
	//	union 
	//	{
	//		struct
	//		{
	//			float x, y;
	//		};
	//
	//		CU::Vector2<float> vec2;
	//	};
	//
	//	//union 
	//	//{
	//	//	CU::Vector2<float> m_position,
	//	//	float x, float y
	//	//};
	//
	//
	//
	//};
}

