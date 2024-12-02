#pragma once
#include "../../../Core/Modules/Module.h"

typedef struct FT_LibraryRec_* FT_Library;

namespace Hi_Engine
{
	struct TextRenderData;
	
	class TextRenderer : public Module, public EventListener
	{
	public:
		TextRenderer(int initOrder);
		~TextRenderer();

		bool Init() override;
		void Shutdown() override;
		// void HandleEvent(class TextRenderEvent& event);

		// void LoadFont(const std::string& aPath, unsigned aFontSize);	// Register font instead?
		void Render(const TextRenderData& data, glm::mat4 projection);
		// Pass in alignment for text...



		// Here? make static in font class?
		static float CalculateTextWidth(const std::string& text, std::shared_ptr<class Font> font, float scale);

		float GetTextStartPosition(const TextRenderData& data);


		inline static FT_Library ft;  // TEMP... (maybe load fonts from here? or have module for FreeType??

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