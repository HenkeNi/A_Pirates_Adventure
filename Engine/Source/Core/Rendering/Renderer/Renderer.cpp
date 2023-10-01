#include "Pch.h"
#include "Renderer.h"
#include "Data/Constants.h"
#include "../Material/Material.h"
#include "../Texture/Subtexture2D.h"
#include "../Camera/Camera.h" // TEMP..
#include "../Window/Window.h"
#include "../Shader/Shader.h"

#define INDICES_PER_QUAD 6
#define VERTICES_PER_QUAD 4

namespace Hi_Engine
{
	void GenerateIndices(uint32_t* someIndices)
	{
		uint32_t offset = 0;

		/* Generate all available indices */
		for (auto i = 0; i < Constants::MaxIndexCount; i += 6)
		{
			// first triangle
			someIndices[i + 0] = 0 + offset;
			someIndices[i + 1] = 1 + offset;
			someIndices[i + 2] = 2 + offset;

			// second triangle
			someIndices[i + 3] = 2 + offset;
			someIndices[i + 4] = 3 + offset;
			someIndices[i + 5] = 0 + offset;

			offset += 4;
		}
	}

	void SetupVertices(Vertex** aTarget, const Transform& aTransform, const glm::vec4& aColor, const glm::vec2* someTexCoords, float aTexIndex)
	{
		static glm::vec4 vertexCoords[4] = {
			{ -0.5f, -0.5f, 0.f, 1.f },
			{  0.5f, -0.5f, 0.f, 1.f },
			{  0.5f,  0.5f, 0.f, 1.f },
			{ -0.5f,  0.5f, 0.f, 1.f }
		};

		static glm::vec3 rotationAxis = { 1.f, 0.f, 0.f };

		// Create a transformation matrix
		glm::mat4 transform = glm::mat4(1.f);
		transform = glm::translate(transform, glm::vec3(aTransform.Position.x, aTransform.Position.y, aTransform.Position.z));
		transform = glm::rotate(transform, glm::radians(aTransform.Rotation), rotationAxis);
		transform = glm::scale(transform, glm::vec3(aTransform.Scale.x, aTransform.Scale.y, 1.0f));

		for (int i = 0; i < VERTICES_PER_QUAD; ++i)
		{
			(*aTarget)->Position = transform * vertexCoords[i];
			(*aTarget)->Color = aColor;
			(*aTarget)->TexCoords = someTexCoords[i];
			(*aTarget)->TexIndex = aTexIndex + 0.1f;	// small hack; makes it 1.1 instead of 1.0 (shader error when converting it to an int)
			++(*aTarget);
		}
	}

	Renderer::Renderer()
		// : m_buffer{ new Vertex[Constants::maxVertexCount] }, m_currentVertex{ nullptr }
	{
		Dispatcher::GetInstance().Subscribe(this);

		m_quadContext.Buffer = new Vertex[Constants::MaxVertexCount];

		///* Configure render states */
		//glEnable(GL_DEPTH_TEST);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glEnable(GL_BLEND);



		// DO this in init? or elsewhere?
		glGenTextures(1, &m_whiteTexture);
		glBindTexture(GL_TEXTURE_2D, m_whiteTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		uint32_t color = 0xffffffff;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &color);

		m_textureSlots[0] = m_whiteTexture;

		//memset(m_textureSlots + 1, 0, (Constants::maxTextureSlots - 1) * sizeof(uint32_t));

		for (auto i = 1; i < Constants::MaxTextureSlots; ++i)
			m_textureSlots[i] = 0;
	}

	Renderer::~Renderer()
	{
		Dispatcher::GetInstance().Unsubscribe(this);
	}

	void Renderer::HandleEvent(RenderEvent& anEvent)
	{
		// TODO; Maybe add to queue => sort first set camera, set shader, then render stuff, lastly text... 
		
		auto commands = anEvent.GetCommands();

		while (!commands.empty())
		{
			auto command = commands.front();
			if (command.Type == eRenderCommandType::DrawSprite)
			{
				DrawSprite(command.SpriteRenderData);
			}
			else if (command.Type == eRenderCommandType::SetShader)
			{
				// m_activeShader = command.m_shader;
			}
			else if (command.Type == eRenderCommandType::SetCamera)
			{
				m_camera = command.Camera;
			}

			commands.pop();
		}
	}

	bool Renderer::IsTextureBound(unsigned aTexID, float& outTexIndex)
	{
		for (uint32_t i = 1; i < m_textureSlotIndex; ++i)
		{
			if (m_textureSlots[i] == aTexID)
			{
				outTexIndex = (float)i;
				return true;
			}
		}
		return false;
	}

	void Renderer::DrawSprite(const SpriteRenderData& someData)
	{
		unsigned id = someData.Subtexture->GetTexture().GetID();

		float textureIndex = 0;

		/* Check if this texture is already bound to a slot */
		if (!IsTextureBound(id, textureIndex))
		{
			textureIndex = (float)m_textureSlotIndex;
			m_textureSlots[m_textureSlotIndex] = id;

			++m_textureSlotIndex;
		}

		if (m_quadContext.IndexCount >= Constants::MaxIndexCount)
		{
			Display();
			BeginFrame();
		}

		SetupVertices(&m_quadContext.CurrentVertex, someData.Transform, someData.Color, someData.Subtexture->GetTexCoords(), textureIndex);

		m_quadContext.IndexCount += INDICES_PER_QUAD;
		++m_stats.TotalQuads;
	}

	void Renderer::DrawQuad(const QuadRenderData& someData)
	{
		// Check if buffer is full
		if (m_quadContext.IndexCount >= Constants::MaxIndexCount)
		{
			Display();
			BeginFrame();
		}

		static const glm::vec2 textureCoords[4] = {
			{ 0.f, 0.f },
			{ 1.f, 0.f },
			{ 1.f, 1.f },
			{ 0.f, 1.f }
		};

		SetupVertices(&m_quadContext.CurrentVertex, someData.Transform, someData.Color, textureCoords, 0.f);

		m_quadContext.IndexCount += INDICES_PER_QUAD;
		++m_stats.TotalQuads;
	}

	void Renderer::Init()
	{
		//--------------- Setup Quad Buffers ---------------//

		/* Create vertex array object */
		glGenVertexArrays(1, &m_quadContext.VAO);
		glBindVertexArray(m_quadContext.VAO);

		/* Create vertex buffer object */
		glGenBuffers(1, &m_quadContext.VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_quadContext.VBO);
		glBufferData(GL_ARRAY_BUFFER, Constants::MaxVertexCount * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

		/* Specify layout of the vertex data */

		/* Position Attribute */
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));

		/* Color Attribute */
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));

		/* Texture Coord Attribute */
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

		/* Texture Index */
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexIndex));

		/* Populate indices */
		uint32_t indices[Constants::MaxIndexCount];
		GenerateIndices(indices);

		/* Create element buffer object */
		glCreateBuffers(1, &m_quadContext.EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_quadContext.EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		/* Unbind VBO and VAO */
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);



		//--------------- Setup Text Buffers ---------------//

		glGenVertexArrays(1, &m_textContext.VAO);
		glGenBuffers(1, &m_textContext.VBO);
		glBindVertexArray(m_textContext.VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_textContext.VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void Renderer::Shutdown()
	{
		glDeleteVertexArrays(1, &m_quadContext.VAO);
		glDeleteBuffers(1, &m_quadContext.VBO);
		glDeleteBuffers(1, &m_quadContext.EBO);

		// Todo; Delete texture ??
		glDeleteTextures(1, &m_whiteTexture); // MOVE later?

		delete[] m_quadContext.Buffer;
	}

	void Renderer::BeginFrame()
	{
		assert(m_window && "ERROR: found nullptr when accessing Window!");

		m_window->ClearScreen();

		/* Set current vertex to point to the first element */
		m_quadContext.CurrentVertex = m_quadContext.Buffer;
		m_quadContext.IndexCount = 0;
		m_textureSlotIndex = 1;
	}

	void Renderer::Display()
	{
		DisplayQuads();
		// DisplayText();
	}

	void Renderer::EndFrame()
	{
		assert(m_window && "ERROR: found nullptr when accessing Window!");
		m_window->SwapBuffers();

		// Reset stats
		m_stats.TotalDraws = 0;
		m_stats.TotalQuads = 0;
	}
	
	void Renderer::SetRenderTarget(Window* aWindow)
	{
		m_window = aWindow;
	}

	void Renderer::SetShader(Shader* aShader, bool aSpriteShader)
	{
		if (aSpriteShader)
		{
			m_quadContext.Shader = aShader;
			m_quadContext.Shader->Activate();

			int samplers[32];
			for (int i = 0; i < 32; ++i)
				samplers[i] = i;

			m_quadContext.Shader->SetIntArray("uTextures", samplers, 32);
		}
	}

	void Renderer::SetCamera(Camera* aCamera)
	{
		m_camera = aCamera;
	}

	void Renderer::DisplayQuads()
	{
		/* Pass data to the buffer (VBO) */
		GLsizeiptr size = (uint8_t*)m_quadContext.CurrentVertex - (uint8_t*)m_quadContext.Buffer;
		glBindBuffer(GL_ARRAY_BUFFER, m_quadContext.VBO);	
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, m_quadContext.Buffer);

		/* Activate and bind used textures */
		for (uint32_t i = 0; i < m_textureSlotIndex; ++i)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, m_textureSlots[i]);
		}

		// m_activeShader->SetIntArray("uTextures", m_textureSlots, m_textureSlotIndex);	// NEEDED??
		m_quadContext.Shader->Activate();	// Fetch instead from ResourceHolder??

		/* Set view-projection matrix */
		glm::mat4 viewProjection = m_camera->GetViewProjectionMatrix();
		m_quadContext.Shader->SetMatrix4("uViewProjection", viewProjection);

		glBindVertexArray(m_quadContext.VAO);
		glDrawElements(GL_TRIANGLES, m_quadContext.IndexCount, GL_UNSIGNED_INT, nullptr);

		++m_stats.TotalDraws;
	}

	void Renderer::DisplayText()
	{
		auto* shader = m_textContext.Shader;

		shader->Activate();
		shader->SetVector4f("uTextColor", { 1.f, 1.f, 1.f, 1.f }); // TODO; fix color...

		glm::mat4 projection = m_camera->GetProjectionMatrix();
		shader->SetMatrix4("uProjection", projection);

		glActiveTexture(GL_TEXTURE0); // ????????????????????
		glBindVertexArray(m_textContext.VAO);

		// iterate through all characters
		//auto position = someData.m_position;
		//const auto& characters = someData.m_font->m_characters;

		//// position.x -= (someData.m_text.size() * characters.begin()->second.m_size.x) * 0.5f; // TEST!!  


		//for (const char& c : someData.m_text)
		//{
		//	const auto& ch = someData.m_font->m_characters[c];

		//	float xpos = position.x + ch.m_bearing.x * someData.m_scale;
		//	float ypos = position.y - (ch.m_size.y - ch.m_bearing.y) * someData.m_scale;

		//	float w = ch.m_size.x * someData.m_scale;
		//	float h = ch.m_size.y * someData.m_scale;
		//	// update VBO for each character
		//	float vertices[6][4] = {
		//		{ xpos,     ypos + h,   0.0f, 0.0f },
		//		{ xpos,     ypos,       0.0f, 1.0f },
		//		{ xpos + w, ypos,       1.0f, 1.0f },

		//		{ xpos,     ypos + h,   0.0f, 0.0f },
		//		{ xpos + w, ypos,       1.0f, 1.0f },
		//		{ xpos + w, ypos + h,   1.0f, 0.0f }
		//	};
		//	// render glyph texture over quad

		//	//ch.m_texture.Bind();
		//	ResourceHolder<Texture2D>::GetInstance().GetResource(ch.m_textureID).Bind();


		//	//glBindTexture(GL_TEXTURE_2D, ch.m_textureID);   // use texture pointer instead..

		//	// update content of VBO memory
		//	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		//	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

		//	glBindBuffer(GL_ARRAY_BUFFER, 0);
		//	// render quad
		//	glDrawArrays(GL_TRIANGLES, 0, 6);
		//	// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		//	position.x += (ch.m_advance >> 6) * someData.m_scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))



		//	//  glBindTexture(GL_TEXTURE_2D, 0); // TEST

		//}

		//glBindVertexArray(0);
		//glBindTexture(GL_TEXTURE_2D, 0);
	}	
}