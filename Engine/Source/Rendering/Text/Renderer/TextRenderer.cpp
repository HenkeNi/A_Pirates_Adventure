#include "Pch.h"
#include "TextRenderer.h"
#include "../../Shader/Shader.h"
#include "../../Texture/Texture2D.h" // TODO; remove---
#include "../../Text/Font/Font.h"
#include "Resources/ResourceHolder.h"
#include "../../Text/TextTypes.h"
//#include "Messaging/Events/RenderEvents/RenderEvents.h"

namespace Hi_Engine
{
    TextRenderer::TextRenderer()
        : m_windowSize{ 1400, 800 }
	{
       // EventDispatcher::GetInstance().Subscribe(this);
    }
	
	TextRenderer::~TextRenderer()
	{
        //EventDispatcher::GetInstance().Unsubscribe(this);
	}

	bool TextRenderer::Initialize()
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

        // Initialize (and load) the FreeType library
        if (FT_Init_FreeType(&ft))
            assert(false && "ERROR: Could not init FreeType Library");

        return true;
	}

	void TextRenderer::Shutdown()
	{}

    /*void TextRenderer::HandleEvent(TextRenderEvent& event)
    {
        Render(event.GetData(), event.GetProjection());
    }*/

	void TextRenderer::Render(const TextRenderData& data, glm::mat4 projection) // pass in projection matrix?
	{
        auto[shader, font, scale, color, position, text, alignment] = data;

        shader->Activate();
        shader->SetVector4f("uTextColor", color);

        glm::mat4 projectionMatrix = glm::ortho(0.0f, (float)m_windowSize.x, 0.0f, (float)m_windowSize.y);
        shader->SetMatrix4("uProjection", projectionMatrix);
      
        glActiveTexture(GL_TEXTURE0); // ????????????????????
        glBindVertexArray(m_textContext.VAO);

        auto startPosition = position;
        auto endPosition = startPosition;

        float textWidth = 0.f;

        position.x = GetTextStartPosition(data);

        for (const char& c : text)
        {
            const auto& ch = font->m_characters[c];
              
            float xPos = 0.f;
            float yPos = 0.f;

            if (c == '\n')
            {
                position.y -= (ch.Size.y) * 1.3 * scale;
                position.x = startPosition.x;
            }
            else if (c == ' ')
            {
                position.x += (ch.m_advance >> 6) * scale;
            }
            else
            {
                float xPos = position.x + ch.m_bearing.x * scale;
                float yPos = position.y - (ch.Size.y - ch.m_bearing.y) * scale;
                    
                float w = ch.Size.x * scale;
                float h = ch.Size.y * scale;

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

                ResourceHolder<Texture2D>::GetInstance().GetResource(ch.m_textureID)->Bind();

                // update content of VBO memory
                glBindBuffer(GL_ARRAY_BUFFER, m_textContext.VBO);
                glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData
                glBindBuffer(GL_ARRAY_BUFFER, 0);

                glDrawArrays(GL_TRIANGLES, 0, 6);

                position.x += (ch.m_advance >> 6) * scale;
            }           
        }

        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
	}

    float TextRenderer::CalculateTextWidth(const std::string& text, std::shared_ptr<class Font> font, float scale)
    {
        float width = 0.f;

        for (const char& ch : text)
        {
            const auto& character = font->m_characters[ch];
            width += (character.m_advance >> 6) * scale;
        }
        return width;
    }

    float TextRenderer::GetTextStartPosition(const TextRenderData& data)
    {
        if (data.Alignment == eTextAlginment::Align_Left)
            return data.Position.x;
        
        float width = CalculateTextWidth(data.Text, data.Font, data.Scale);
        
        if (data.Alignment == eTextAlginment::Align_Center)
        {
            return data.Position.x - (width * 0.5f);
        }
        else if (data.Alignment == eTextAlginment::Align_Right)
        {
            return data.Position.x + (width * 0.5f);
        }



        return 0.0f;
    }
}