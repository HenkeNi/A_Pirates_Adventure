#pragma once
#include "../Utility/Math/Vectors/Vector.hpp"
#include "../Core/Messaging/Events/Event.h"
#include <functional>

namespace CU = CommonUtilities;

// Todo; change naming convention for structs?? Position rather than m_position?

namespace Hi_Engine
{
	struct VertexData // use??
	{
		CU::Vector3<float> m_position;
		CU::Vector2<float> m_textCoord;
	};

	struct WindowData
	{
		CU::Vector2<unsigned>	m_size;
		std::string				m_identifier, m_iconPath;
	};




	//struct CameraData
	//{
	//	CU::Vector3<float>	m_position  = { 0.f, 0.f,  3.f };
	//	CU::Vector3<float>	m_front		= { 0.f, 0.f, -1.f }; // m_right; // make struct for coordinate system?		Rename m_forwardDir;
	//	CU::Vector3<float>	m_up		= { 0.f, 1.f,  0.f };					// reame m_upDir;
	//	//CU::Vector3<float>	m_worldUp;

	//	//float				m_movementSpeed, m_zoomSpeed;
	//};


	struct CameraAttributes
	{
		glm::vec3 m_position;	// change to glm::vec3??
		glm::vec3 m_front;
		glm::vec3 m_up;
		glm::vec3 m_right;
		glm::vec3 m_worldUp;
	};

	struct EulerAngles
	{
		float m_yaw;
		float m_pitch;
		float m_roll;
	};



	class Texture2D;
	
	struct SpriteRenderData
	{
		Texture2D&			m_texture;
		CU::Vector4<float>	m_color;
		CU::Vector3<float>	m_position;
		CU::Vector3<float>	m_size;			// Rename Scale?? vec2 or vec3
		float				m_rotation;

		//CameraData			m_cameraData;
	};


	struct TextureData
	{

	};





	struct Quad	// or QuadVertex , QuadData?? combine with render data somehow??
	{
		CU::Vector4<float> m_color;
		CU::Vector3<float> m_position;
		CU::Vector2<float> m_texCoord;
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



	/* Comparers */
	struct EventCompare
	{
		bool operator()(const Event* aFirst, const Event* aSecond)
		{
			return aFirst->GetPriority() < aSecond->GetPriority();
		}
	};

}

