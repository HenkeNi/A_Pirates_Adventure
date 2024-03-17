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


	void TextRenderer::Render(const TextRenderData& data, glm::mat4 projection) // pass in projection matrix?
	{
        auto& shader = data.Shader;

        shader->Activate();
        shader->SetVector4f("uTextColor", data.Color);

        glm::mat4 projectionMatrix = glm::ortho(0.0f, (float)m_windowSize.x, 0.0f, (float)m_windowSize.y);
        shader->SetMatrix4("uProjection", projectionMatrix);
      
        glActiveTexture(GL_TEXTURE0); // ????????????????????
        glBindVertexArray(m_textContext.VAO);

        auto position = data.Position;
        auto scale = data.Scale;

        for (const char& c : data.Text)
        {
            const auto& ch = data.Font->m_characters[c];
                     
            float xPos = position.x + ch.m_bearing.x * scale;
            float yPos = position.y - (ch.Size.y - ch.m_bearing.y) * scale;

            float w = ch.Size.x * scale;
            float h = ch.Size.y * scale;
            
            CU::Vector4<float> color = data.Color;

            // update VBO for each character
            float vertices[6][8] = 
            {   
                // Position             // Color                                // Texture coords
                { xPos,     yPos + h,   color.x, color.y, color.z, color.w,     0.0f, 0.0f },
                { xPos,     yPos,       color.x, color.y, color.z, color.w,     0.0f, 1.0f },
                { xPos + w, yPos,       color.x, color.y, color.z, color.w,     1.0f, 1.0f },

                { xPos,     yPos + h,   color.x, color.y, color.z, color.w,     0.0f, 0.0f },
                { xPos + w, yPos,       color.x, color.y, color.z, color.w,     1.0f, 1.0f },
                { xPos + w, yPos + h,   color.x, color.y, color.z, color.w,     1.0f, 0.0f }
            };
            // render glyph texture over quad

            //ch.m_texture.Bind();
            ResourceHolder<Texture2D>::GetInstance().GetResource(ch.m_textureID).Bind();
            //glBindTexture(GL_TEXTURE_2D, ch.m_textureID);   // use texture pointer instead..
           
            // update content of VBO memory
            glBindBuffer(GL_ARRAY_BUFFER, m_textContext.VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            glDrawArrays(GL_TRIANGLES, 0, 6);

            position.x += (ch.m_advance >> 6) * data.Scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
        }
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
	}

}