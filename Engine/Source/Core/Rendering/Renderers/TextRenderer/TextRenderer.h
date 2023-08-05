#pragma once
#include "Data/Structs.h"

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

		void LoadFont(const std::string& aPath, unsigned aFontSize);	// Register font instead?
		void Render(const TextRenderData& someData);

	private:
		TextRenderer();

		class Camera* m_camera;
		CU::Vector2<unsigned>	m_windowSize;	// FIX LATER...
		unsigned	m_VAO, m_VBO;

		std::unordered_map<GLchar, Character>   m_characters;

		// TODO; store text/fonts in resource holder?!
	};
}