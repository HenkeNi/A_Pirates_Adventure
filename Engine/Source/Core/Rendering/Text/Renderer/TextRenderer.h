#pragma once
#include "../../../../Data/Structs.h"
#include "../../../Modules/Base/Module.h"

namespace Hi_Engine
{
	struct TextRenderData;
	
	class TextRenderer : public Module, public EventListener
	{
	public:
		TextRenderer(int initOrder);
		~TextRenderer();
		//TextRenderer(const TextRenderer&)				= delete;
		//TextRenderer& operator=(const TextRenderer&)	= delete;

		//static TextRenderer& GetInstance();

		bool Init() override;
		void Shutdown() override;
		void HandleEvent(class TextRenderEvent& event);

		// void LoadFont(const std::string& aPath, unsigned aFontSize);	// Register font instead?
		void Render(const TextRenderData& data, glm::mat4 projection);
		// Pass in alignment for text...



		// Here? make static in font class?
		static float CalculateTextWidth(const std::string& text, class Font* font, float scale);

		float GetTextStartPosition(const TextRenderData& data);


	private:


		RenderContext	m_textContext;


		// class Camera* m_camera;
		UVector2	m_windowSize;	// FIX LATER...
		// unsigned	m_VAO, m_VBO;

		//std::unordered_map<GLchar, Character>   m_characters;
		//class GLSLShader* m_textShader;
		// TODO; store text/fonts in resource holder?!
	};
}