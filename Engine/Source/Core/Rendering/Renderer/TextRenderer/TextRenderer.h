#pragma once
#include "../../../../Data/Structs.h"

namespace Hi_Engine
{
	namespace CU = CommonUtilities;

	struct TextRenderData;
	

	class TextRenderer
	{
	public:
		~TextRenderer();
		TextRenderer(const TextRenderer&)				= delete;
		TextRenderer& operator=(const TextRenderer&)	= delete;

		static TextRenderer& GetInstance();

		void Init();
		void Shutdown();

		// void LoadFont(const std::string& aPath, unsigned aFontSize);	// Register font instead?
		void Render(const TextRenderData& data, glm::mat4 projection);
		// Pass in alignment for text...



		// Here?
		static float CalculateTextWidth(const std::string& text, class Font* font, float scale);

		float GetTextStartPosition(const TextRenderData& data);


	private:
		TextRenderer();


		RenderContext	m_textContext;


		// class Camera* m_camera;
		CU::Vector2<unsigned>	m_windowSize;	// FIX LATER...
		// unsigned	m_VAO, m_VBO;

		//std::unordered_map<GLchar, Character>   m_characters;
		//class Shader* m_textShader;
		// TODO; store text/fonts in resource holder?!
	};
}