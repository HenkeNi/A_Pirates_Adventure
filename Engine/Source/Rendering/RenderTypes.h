#pragma once
//#include "../Core/Math/Vectors/Vector.hpp"
#include <../../ThirdParty/glm/glm.hpp>
//#include <array>
//#include <string>
//#include <vector>

namespace Hi_Engine
{
	// MOVE TRANSFORM!!!!
	struct Transform
	{
		glm::vec3	Position = { 0.f, 0.f, 0.f }; // change to FVector2?
		glm::vec2	Scale = { 1.f, 1.f };
		float		Rotation = 0.f;
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
	/////////////////////////////////////////

	struct Vertex
	{
		glm::vec3	Position;  // float Position[3];		// Change to CU::Vector3 instead??
		glm::vec4	Color;	   // float Color[4];			
		glm::vec2	TexCoords; // float TexCoords[2];		
		float		TexIndex;
		//GLint		TexIndex;
	};

	struct Sprite
	{
		Transform Transform{};
		glm::vec4 Color = { 1.f, 1.f, 1.f, 1.f };
		const class Subtexture2D* Subtexture = nullptr; // FIX???
	};

	struct SpriteBatch // renaem render batch??
	{
		std::vector<Sprite> Sprites;
		glm::mat4 ProjectionMatrix;
	};


	// NEEDED or can use Sprite?
	struct SpriteRenderData
	{
		const class Subtexture2D* Subtexture = nullptr;
		glm::vec4					Color = { 1.f, 1.f, 1.f, 1.f };
		Transform					Transform{};

		//glm::vec3					Position;	// Vector3<float>
		//glm::vec2					Scale;		// Rename size?? Vector2<float>
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

	// Rename TextRenderProperties?

	struct RenderContext
	{
		class GLSLShader* GLSLShader = nullptr;
		Vertex* Buffer = nullptr;
		Vertex* CurrentVertex = nullptr;		// unsigned	m_currentBufferIndex;
		uint16_t			IndexCount = 0;
		unsigned			VAO = 0, VBO = 0, EBO = 0;
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






	/////////////////// MOVE??? to render event class?
	enum class eRenderCommandType
	{
		SetShader,
		SetProjectionMatrix,
		DrawSprite,
		DrawBatch
	};

	struct RenderCommand
	{
		//SpriteRenderData RenderData;

		eRenderCommandType		Type;

		union
		{
			//std::vector<SpriteRenderData>	SpriteBatch;
			//SpriteBatchData					SpriteBatchData;
			//class Camera*					Camera;
			SpriteRenderData				SpriteRenderData;
			class GLSLShader* GLSLShader;
			glm::mat4						ProjectionMatrix;
		};
	};

	struct BatchRendering
	{
		class GLSLShader* ShaderOverride;
		glm::mat4 ProjectionMatrix;
	};

	//////////////////////////

}