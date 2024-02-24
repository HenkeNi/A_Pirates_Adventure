#pragma once
#include "../Utility/Math/Vectors/Vector.hpp"
#include "../Core/Messaging/Events/Event.h"
#include "../Core/Rendering/Texture/Texture2D.h"

#include <../../ThirdParty/glm/glm.hpp>
// #include <../glm/glm.hpp>
#include <../../ThirdParty/GLEW/include/GL/glew.h>
#include <array>
#include <functional>
#include <string>
#include <vector>

namespace CU = CommonUtilities;

// Todo; change naming convention for structs?? Position rather than m_position?

namespace Hi_Engine
{
#pragma region Utility_Structs	

	template <typename Type>
	struct Point
	{
		Type X;
		Type Y;
	};

	struct Transform
	{
		glm::vec3	Position = { 0.f, 0.f, 0.f };
		glm::vec2	Scale = { 1.f, 1.f };
		float		Rotation = 0.f;
	};

	struct TimerRequest
	{
		double					DurationInSecs, TimeOfRequest;
		std::function<void()>	Callback = nullptr;

		//TimeObserver*			m_observer = nullptr;
	};

	template <typename T>
	struct HitResult
	{
		bool			IsColliding = false;
		CU::Vector2<T>	ContactPoint { 0, 0 };
		CU::Vector2<T>	ContactNormal{ 0, 0 };

		// Union?
		float ContactTime = 0;	// BEEDED???
		float THitNear = 0;
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

#pragma region Camera_Structs

	// TODO: Remove?!
	/*struct CameraMatrices
	{
		glm::mat4 View{ 1.f };
		glm::mat4 Projection;
		glm::mat4 ProjectionView;
	};

	struct CameraAttributes
	{
		glm::vec3 Position;
		glm::vec3 Front;
		glm::vec3 Up;
		glm::vec3 Right;
		glm::vec3 WorldUp;
	};

	struct EulerAngles
	{
		float Yaw;
		float Pitch;
		float Roll;
	};*/

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
		CU::Vector2<unsigned>	Size;
		std::string				Identifier, IconPath;
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

	struct Text
	{
		glm::vec2	Position;
		glm::vec4	Color;
		glm::vec2	TexCoords;
	};

	struct Character
	{
		std::string		m_textureID;
		glm::ivec2		Size;       // Size of glyph
		glm::ivec2		m_bearing;    // Offset from baseline to left/top of glyph
		unsigned int	m_advance;    // Offset to advance to next glyph
	};

	struct SpriteRenderData
	{
		// const class Material*	Material;
		const class Subtexture2D*	Subtexture = nullptr;
		glm::vec4					Color = { 1.f, 1.f, 1.f, 1.f };
		Transform					Transform{};

		//glm::vec3					Position;	// CU::Vector3<float>
		//glm::vec2					Scale;		// Rename size?? CU::Vector2<float>
		//float						Rotation;
	};	

	struct SpriteBatchData
	{
		std::vector<SpriteRenderData>	SpriteData;
		glm::vec4						ProjectionMatrix;
	};

	struct QuadRenderData
	{
		Transform			Transform;
		glm::vec4			Color;
		//glm::vec3			Position;
		//glm::vec2			Scale;
		//float				Rotation;
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
		class Shader*		Shader;
		class Font*			Font;
		float				Scale;
		CU::Vector4<float>	Color;
		CU::Vector2<float>	Position; //??
		std::string			Text;
	};
	
	//struct PrimitiveRenderData
	//{
	//	CU::Vector4<float>	m_color;
	//	// class Shader*		m_shader;
	//	glm::vec3			Position;
	//	glm::vec2			Scale;
	//	float				Rotation;
	//};




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
		bool operator()(const BaseEvent* aFirst, const BaseEvent* aSecond)
		{
			return aFirst->GetPriority() < aSecond->GetPriority();
		}
	};

	struct RenderCommand
	{
		//SpriteRenderData RenderData;

		eRenderCommandType		Type;

		union
		{
			//std::vector<SpriteRenderData>	SpriteBatch;
			SpriteRenderData				SpriteRenderData;
			//SpriteBatchData					SpriteBatchData;
			class Shader*					Shader;
			class Camera*					Camera;
			glm::mat4						ProjectionMatrix;
		};
	};

#pragma endregion Event_Structs
}