#pragma once
#include "../Utility/Math/Vectors/Vector.hpp"

namespace CU = CommonUtilities;


struct WindowData
{
	CU::Vector2<unsigned>	m_size;
	std::string				m_name, m_iconPath;
};


// Put in Game??
class InputHandler;
class Window;

struct SharedContext 
{
	// SceneManagerProxy	m_sceneManager;
	// Window&				m_window;
	InputHandler&		m_inputHandler;
};


//??
struct Position
{

	union 
	{
		struct
		{
			float x, y;
		};

		CU::Vector2<float> vec2;
	};

	//union 
	//{
	//	CU::Vector2<float> m_position,
	//	float x, float y
	//};



};