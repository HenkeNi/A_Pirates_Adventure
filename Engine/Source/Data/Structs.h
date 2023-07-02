#pragma once
#include "../Utility/Math/Vectors/Vector.hpp"
#include "../Core/Messaging/Events/Event.h"
#include <functional>

#include <../glm/glm.hpp>
//#include "../glm/glm.hpp"
//#include <GL/glew.h>
#include <../GLEW/include/GL/glew.h>
#include <array>

namespace CU = CommonUtilities;

// Todo; change naming convention for structs?? Position rather than m_position?

namespace Hi_Engine
{
	struct CameraMatrices
	{
		glm::mat4 View{ 1.f };
		glm::mat4 Projection;
		glm::mat4 ProjectionView;
	};





	struct Vertex	// rename VertexData or VertexLayout? change to CU::Vector instead? or glm::vec3
	{
		glm::vec3	Position; // Change to CU::Vector3 instead??
		glm::vec4	Color;
		glm::vec2	TexCoords;
		float		TexIndex;
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


	class Material;
	class Texture2D;
	class Shader;

	struct SpriteRenderData
	{
		const Material*				Material;
		glm::vec3					Position; // CU::Vector3<float>
		glm::vec2					Scale;			// Rename Scale or Size?? CU::Vector2<float>
		float						Rotation;
	};

	class Camera;
	struct SpriteData
	{
		const Texture2D*			m_texture;
		const Shader*				m_shader;
		const CU::Vector4<float>	m_color;
		const CU::Vector3<float>	m_position;
		const CU::Vector3<float>	m_size;			// Rename Scale?? vec2 or vec3
		const float					m_rotation;

		Camera*						m_cameraData;
	};

	struct BillboardRenderData
	{
		const Material*				Material;
		glm::vec3					Position;
		glm::vec2					Scale;
		float						Rotation;
	};

	struct SpriteRendererData // rename renderer data??
	{
		GLuint QuadVA = 0;	// Put in SpriteRendere instead??
		GLuint QuadVB = 0;
		GLuint QuadIB = 0;

		GLuint WhiteTexture = 0;
		uint32_t WhiteTextureSlot = 0;

		uint32_t IndexCount = 0;			// How many indices needs to be drawn...

		Vertex* QuadBuffer = nullptr;
		Vertex* QuadBufferPtr = nullptr;

		static const size_t MaxTextures = 32;

		std::array<uint32_t, MaxTextures> TextureSlots;
		uint32_t TextureSlotIndex = 1;
	};



	struct PrimitiveRenderData
	{
		CU::Vector3<float>	m_color;
		class Shader*		m_shader;
		glm::vec3			Position;
		glm::vec2			Scale;
		float				Rotation;
	};

	struct TextureData
	{

	};



	struct Rect
	{
		float Top;
		float Bottom;
		float Left;
		float Right;
	};



	struct Quad	// or QuadVertex , QuadData?? combine with render data somehow??
	{
		CU::Vector4<float> m_color;
		CU::Vector3<float> m_position;
		CU::Vector2<float> m_texCoord;
	};


	template <typename Type>
	struct Point
	{
		Type m_X;
		Type m_Y;
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

