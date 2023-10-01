#include "Pch.h"
#include "TextRenderer.h"
#include "Data/Structs.h"
#include "../../Shader/Shader.h"
#include "../../Texture/Texture2D.h" // TODO; remove---
#include "../../Font/Font.h"
#include "Resources/ResourceHolder.hpp"


namespace Hi_Engine
{
	TextRenderer::TextRenderer()
        : m_windowSize{ 1400, 800 }
	{}
	
	TextRenderer::~TextRenderer()
	{
	}

	TextRenderer& TextRenderer::GetInstance()
	{
        static TextRenderer instance;
        return instance;
	}

	void TextRenderer::Init()
	{
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
	}

	void TextRenderer::Shutdown()
	{}


	void TextRenderer::Render(const TextRenderData& someData)
	{
        return;

        // activate corresponding render state	
        someData.Shader->Activate();
        someData.Shader->SetVector3f("uTextColor", someData.Color);

        glm::mat4 projection = glm::ortho(0.0f, (float)m_windowSize.x, 0.0f, (float)m_windowSize.y);
        someData.Shader->SetMatrix4("uProjection", projection);
      
        glActiveTexture(GL_TEXTURE0); // ????????????????????
        glBindVertexArray(m_VAO);

        // iterate through all characters
        auto position = someData.Position;
        const auto& characters = someData.Font->m_characters;

        // position.x -= (someData.m_text.size() * characters.begin()->second.m_size.x) * 0.5f; // TEST!!  

        
        for (const char& c : someData.Text)
        {
            const auto& ch = someData.Font->m_characters[c];
                     
            float xpos = position.x + ch.m_bearing.x * someData.Scale;
            float ypos = position.y - (ch.Size.y - ch.m_bearing.y) * someData.Scale;

            float w = ch.Size.x * someData.Scale;
            float h = ch.Size.y * someData.Scale;
            // update VBO for each character
            float vertices[6][4] = {
                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos,     ypos,       0.0f, 1.0f },
                { xpos + w, ypos,       1.0f, 1.0f },

                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos + w, ypos,       1.0f, 1.0f },
                { xpos + w, ypos + h,   1.0f, 0.0f }
            };
            // render glyph texture over quad

            //ch.m_texture.Bind();
            ResourceHolder<Texture2D>::GetInstance().GetResource(ch.m_textureID).Bind();


            //glBindTexture(GL_TEXTURE_2D, ch.m_textureID);   // use texture pointer instead..
            
            // update content of VBO memory
            glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            // render quad
            glDrawArrays(GL_TRIANGLES, 0, 6);
            // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            position.x += (ch.m_advance >> 6) * someData.Scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
            
            
            
           //  glBindTexture(GL_TEXTURE_2D, 0); // TEST

        }

        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
	}

}