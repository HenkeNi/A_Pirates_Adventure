#pragma once
#include "../Utility/Math/Vectors/Vector.hpp"
#include "Enumerations.h"
#include <../../ThirdParty/glm/glm.hpp>
#include <array>
#include <string>
#include <vector>


namespace Hi_Engine
{
	using namespace Math;

#pragma region Utility_Structs	

	// Todo, function "IsInsideRange" etc?

	struct Transform
	{
		glm::vec3	Position = { 0.f, 0.f, 0.f };
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

#pragma endregion Utility_Structs	

#pragma region Camera_Structs

	// Remove later? or using for vec4 together with color?
	struct Rect
	{
		float Top;
		float Bottom;
		float Left;
		float Right;
	};

#pragma endregion Camera_Structs

#pragma region Rendering_Structs

	struct Vertex	
	{
		glm::vec3	Position;  // float Position[3];		// Change to CU::Vector3 instead??
		glm::vec4	Color;	   // float Color[4];			
		glm::vec2	TexCoords; // float TexCoords[2];		
		float		TexIndex;
		//GLint		TexIndex;
	};

	struct SpriteRenderData
	{
		// const class Material*	Material;
		const class Subtexture2D*	Subtexture = nullptr;
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
		class GLSLShader*		GLSLShader			= nullptr;
		Vertex*				Buffer			= nullptr;
		Vertex*				CurrentVertex	= nullptr;		// unsigned	m_currentBufferIndex;
		uint16_t			IndexCount		= 0;
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

#pragma endregion Rendering_Structs


#pragma region Event_Structs
	


	struct RenderCommand
	{
		//SpriteRenderData RenderData;

		eRenderCommandType		Type;

		union
		{
			//std::vector<SpriteRenderData>	SpriteBatch;
			SpriteRenderData				SpriteRenderData;
			//SpriteBatchData					SpriteBatchData;
			class GLSLShader*					GLSLShader;
			class Camera*					Camera;
			glm::mat4						ProjectionMatrix;
		};
	};

#pragma endregion Event_Structs


	struct SubtextureData
	{
		std::string TextureName;
		int Row;
		int Column;

		bool operator==(const SubtextureData& other) const {
			return (TextureName == other.TextureName && Row == other.Row && Column == other.Column);
		}
	};


}

template <>
struct std::hash<Hi_Engine::SubtextureData> {

	std::size_t operator()(const Hi_Engine::SubtextureData& subtexture) const {
		std::size_t res = 17;
		res = res * 31 + std::hash<std::string>()(subtexture.TextureName);
		res = res * 31 + std::hash<int>()(subtexture.Row);
		res = res * 31 + std::hash<int>()(subtexture.Column);

		return res;
	}
};