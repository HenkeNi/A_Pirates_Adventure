#pragma once
#include "../Utility/Math/Vectors/Vector.hpp"
#include "../Core/Messaging/Events/Event.h"
#include "../Core/Rendering/Texture/Texture2D.h"

#include <../../ThirdParty/glm/glm.hpp>
// #include <../glm/glm.hpp>
#include <../../ThirdParty/GLEW/include/GL/glew.h>
#include <array>
#include <functional>

namespace CU = CommonUtilities;

// Todo; change naming convention for structs?? Position rather than m_position?

namespace Hi_Engine
{
#pragma region Camera_Structs

	struct CameraMatrices
	{
		glm::mat4 View{ 1.f };
		glm::mat4 Projection;
		glm::mat4 ProjectionView;
	};

	struct CameraAttributes
	{
		glm::vec3 m_position;
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

	// Remove later?
	struct Rect
	{
		float Top;
		float Bottom;
		float Left;
		float Right;
	};

#pragma endregion Camera_Structs


#pragma region Window_Structs
	
	struct WindowData
	{
		CU::Vector2<unsigned>	m_size;
		std::string				m_identifier, m_iconPath;
	};

#pragma endregion Window_Structs


#pragma region Rendering_Structs

	struct Vertex	
	{
		glm::vec3	Position;  // float Position[3];		// Change to CU::Vector3 instead??
		glm::vec4	Color;	   // float Color[4];			
		glm::vec2	TexCoords; // float TexCoords[2];		
		float		TexIndex;
		//GLint		TexIndex;
	};

	struct Character
	{
		std::string		m_textureID;
		glm::ivec2		m_size;       // Size of glyph
		glm::ivec2		m_bearing;    // Offset from baseline to left/top of glyph
		unsigned int	m_advance;    // Offset to advance to next glyph
	};

	struct SpriteRenderData
	{
		// const class Material*	Material;
		const class Subtexture2D*		m_subtexture;
		glm::vec3				Position;	// CU::Vector3<float>
		glm::vec2				Scale;		// Rename size?? CU::Vector2<float>
		float					Rotation;

		// key to shader, and key to texture..
	};

	//struct SpriteSheetData
	//{
	//	class Subtexture2D*		m_subtexture;
	//	glm::vec3				Position;
	//	glm::vec2				Scale;
	//	float					Rotation;
	//};
	
	struct TextRenderData
	{
		class Shader* m_shader;
		class Font* m_font;
		float				m_scale;
		CU::Vector3<float>	m_color;
		CU::Vector2<float>	m_position; //??
		std::string			m_text;
	};
	
	struct PrimitiveRenderData
	{
		CU::Vector4<float>	m_color;
		// class Shader*		m_shader;
		glm::vec3			Position;
		glm::vec2			Scale;
		float				Rotation;
	};

	struct QuadRenderData
	{
		glm::vec3			Position;
		glm::vec4			Color;
		glm::vec2			Scale;
		float				TexIndex;
		float				Rotation;
	};


	struct RenderContext
	{
		class Shader*		Shader			= nullptr;
		Vertex*				Buffer			= nullptr;
		Vertex*				CurrentVertex	= nullptr;		// unsigned	m_currentBufferIndex;
		uint16_t			IndexCount		= 0;
		unsigned			VAO, VBO, EBO;
	};

	struct RenderStats
	{
		unsigned TotalDraws = 0;
		unsigned TotalQuads = 0;
	};

	struct LineRenderData
	{

	};


	struct RectRenderData
	{};



	struct SpriteSheet
	{
	};

#pragma endregion Rendering_Structs


#pragma region Event_Structs

	/* Comparers */
	struct EventCompare
	{
		bool operator()(const Event* aFirst, const Event* aSecond)
		{
			return aFirst->GetPriority() < aSecond->GetPriority();
		}
	};

	struct RenderCommand
	{
		eRenderCommandType		m_type;

		union
		{
			SpriteRenderData	m_spriteRenderData;
			class Shader*		m_shader;
			class Camera*		m_camera;
		};
	};

#pragma endregion Event_Structs


#pragma region Utility_Structs	

	template <typename Type>
	struct Point
	{
		Type m_X;
		Type m_Y;
	};

	struct TimerRequest
	{
		double					m_durationInSecs, m_timeOfRequest;
		std::function<void()>	m_callback = nullptr;

		//TimeObserver*			m_observer = nullptr;
	};

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

#pragma endregion Utility_Structs	
}