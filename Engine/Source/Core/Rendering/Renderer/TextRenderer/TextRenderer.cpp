#include "Pch.h"
#include "TextRenderer.h"
#include "../Data/Structs.h"
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
        return;

        glGenVertexArrays(1, &m_textContext.VAO);
        glBindVertexArray(m_textContext.VAO);

        glGenBuffers(1, &m_textContext.VBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_textContext.VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * sizeof(Text), nullptr, GL_DYNAMIC_DRAW); // FIX THE SIZE of the buffer!

        /* Position Attribute */
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Text), (void*)offsetof(Text, Position));

        /* Color Attribute */
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Text), (void*)offsetof(Text, Color));

        /* Texture Coord Attribute */
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Text), (void*)offsetof(Text, TexCoords));

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
        glBindVertexArray(m_textContext.VAO);

        // iterate through all characters
        auto position = someData.Position;

        // position.x -= (someData.m_text.size() * characters.begin()->second.m_size.x) * 0.5f; // TEST!!  

        
        for (const char& c : someData.Text)
        {
            const auto& ch = someData.Font->m_characters[c];
                     
            float xPos = position.x + ch.m_bearing.x * someData.Scale;
            float yPos = position.y - (ch.Size.y - ch.m_bearing.y) * someData.Scale;

            float w = ch.Size.x * someData.Scale;
            float h = ch.Size.y * someData.Scale;
            // update VBO for each character
            
            CU::Vector3<float> color = someData.Color;

            float vertices[6][8] = 
            {                           // color                                // Texture coords
                { xPos,     yPos + h,   color.x, color.y, color.z, 1.f,         0.0f, 0.0f },
                { xPos,     yPos,       color.x, color.y, color.z, 1.f,         0.0f, 1.0f },
                { xPos + w, yPos,       color.x, color.y, color.z, 1.f,         1.0f, 1.0f },

                { xPos,     yPos + h,   color.x, color.y, color.z, 1.f,         0.0f, 0.0f },
                { xPos + w, yPos,       color.x, color.y, color.z, 1.f,         1.0f, 1.0f },
                { xPos + w, yPos + h,   color.x, color.y, color.z, 1.f,         1.0f, 0.0f }
            };
            // render glyph texture over quad

            //ch.m_texture.Bind();
            ResourceHolder<Texture2D>::GetInstance().GetResource(ch.m_textureID).Bind();


            //glBindTexture(GL_TEXTURE_2D, ch.m_textureID);   // use texture pointer instead..
            
            // update content of VBO memory
            glBindBuffer(GL_ARRAY_BUFFER, m_textContext.VBO);
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