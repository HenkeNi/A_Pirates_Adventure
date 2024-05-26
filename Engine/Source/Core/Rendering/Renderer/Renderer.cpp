#include "Pch.h"
#include "Renderer.h"
#include "../Data/Constants.h"
#include "../Material/Material.h"
#include "../Texture/Texture2D.h"
#include "../Texture/Subtexture2D.h"
#include "../Camera/Camera.h" // TEMP..
#include "../Shader/Shader.h"
#include "glm.hpp"

#define INDICES_PER_QUAD 6
#define VERTICES_PER_QUAD 4

namespace Hi_Engine
{
	void GenerateIndices(uint32_t* indices)
	{
		uint32_t offset = 0;

		/* Generate all available indices */
		for (auto i = 0; i < Constants::MaxIndexCount; i += 6)
		{
			// first triangle
			indices[i + 0] = 0 + offset;
			indices[i + 1] = 1 + offset;
			indices[i + 2] = 2 + offset;

			// second triangle
			indices[i + 3] = 2 + offset;
			indices[i + 4] = 3 + offset;
			indices[i + 5] = 0 + offset;

			offset += 4;
		}
	}

	void SetupVertices(Vertex** target, const Transform& transform, const glm::vec4& aColor, const glm::vec2* someTexCoords, float aTexIndex)
	{
		static glm::vec4 vertexCoords[4] = {
			{ -0.5f, -0.5f, 0.f, 1.f },
			{  0.5f, -0.5f, 0.f, 1.f },
			{  0.5f,  0.5f, 0.f, 1.f },
			{ -0.5f,  0.5f, 0.f, 1.f }
		};

		static glm::vec3 rotationAxis = { 0.f, 0.f, 1.f };

		// Create a transformation matrix
		glm::mat4 transformMatrix = glm::mat4(1.f);
		transformMatrix = glm::translate(transformMatrix, glm::vec3(transform.Position.x, transform.Position.y, transform.Position.z));
		transformMatrix = glm::rotate(transformMatrix, glm::radians(transform.Rotation), rotationAxis);
		transformMatrix = glm::scale(transformMatrix, glm::vec3(transform.Scale.x, transform.Scale.y, 1.0f));

		for (int i = 0; i < VERTICES_PER_QUAD; ++i)
		{
			(*target)->Position = transformMatrix * vertexCoords[i];
			(*target)->Color = aColor;
			(*target)->TexCoords = someTexCoords[i];
			(*target)->TexIndex = aTexIndex + 0.1f;	// small hack; makes it 1.1 instead of 1.0 (shader error when converting it to an int)
			++(*target);
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

	void Renderer::Init()
	{
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

	void Renderer::HandleEvent(RenderEvent& renderEvent)
	{
		// TODO; Maybe add to queue => sort first set camera, set shader, then render stuff, lastly text... 
		
		auto commands = renderEvent.GetCommands();

		std::queue<RenderCommand> renderCommands;

		while (!commands.empty())
		{
			//m_renderCommands.emplace(commands.front());
			renderCommands.push(commands.front());
			commands.pop();
		}

		m_renderSequence.push(renderCommands);

		//for (auto command : commands)
		//{
		//	if (command.Type == eRenderCommandType::DrawSprite)
		//	{
		//		DrawSprite(command.SpriteRenderData);
		//	}
		//	else if (command.Type == eRenderCommandType::SetShader)
		//	{
		//		// m_activeShader = command.m_shader;
		//	}
		//	else if (command.Type == eRenderCommandType::SetCamera)
		//	{
		//		m_camera = command.Camera;
		//	}
		//}


		//while (!commands.empty())
		//{
		//	auto command = commands.front();
		//	if (command.Type == eRenderCommandType::DrawSprite)
		//	{
		//		DrawSprite(command.SpriteRenderData);
		//	}
		//	else if (command.Type == eRenderCommandType::SetShader)
		//	{
		//		// m_activeShader = command.m_shader;
		//	}
		//	else if (command.Type == eRenderCommandType::SetCamera)
		//	{
		//		m_camera = command.Camera;
		//	}
		//	else if (command.Type == eRenderCommandType::SetProjectionMatrix)
		//	{
		//		glm::mat4 viewProjection = m_camera->GetViewProjectionMatrix();
		//		m_quadContext.GLSLShader->SetMatrix4("uViewProjection", viewProjection);
		//	}

		//	commands.pop();
		//}

	}

	void Renderer::ProcessCommands()
	{
		while (!m_renderSequence.empty())
		{
			BeginFrame(); // FIX!

			auto sequence = m_renderSequence.front();

			//while (!m_renderCommands.empty())
			while (!sequence.empty())
			{
				auto command = sequence.front();
				//auto command = m_renderCommands.front();

				// TODO: if batch,,,,,,
				if (command.Type == eRenderCommandType::DrawBatch)
				{
					// pass projection matrix...

					// Reset();

					// Draw sprites()

				}
				else if (command.Type == eRenderCommandType::DrawSprite)
				{
					DrawSprite(command.SpriteRenderData);
				}
				else if (command.Type == eRenderCommandType::SetShader)
				{
					// m_activeShader = command.m_shader;
				}
				else if (command.Type == eRenderCommandType::SetCamera)
				{
					// m_quadContext.GLSLShader->SetMatrix4("uViewProjection", command.Camera->GetProjectionMatrix());

				}
				else if (command.Type == eRenderCommandType::SetProjectionMatrix)
				{
					//glm::mat4 viewProjection = m_camera->GetViewProjectionMatrix();
					m_quadContext.GLSLShader->SetMatrix4("uViewProjection", command.ProjectionMatrix);
				}

				//m_renderCommands.pop();
				sequence.pop();
			}

			EndFrame();
			m_renderSequence.pop();
		}
	}

	void Renderer::Reset()
	{
		m_quadContext.CurrentVertex = m_quadContext.Buffer;
		m_quadContext.IndexCount = 0;
		m_textureSlotIndex = 1;

		// Reset Stats??
		m_stats.TotalDraws = 0;
		m_stats.TotalQuads = 0;
	}


	void Renderer::DrawSprite(const SpriteRenderData& data)
	{
		unsigned id = data.Subtexture->GetTexture().GetID();

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

		SetupVertices(&m_quadContext.CurrentVertex, data.Transform, data.Color, data.Subtexture->GetTexCoords(), textureIndex);

		m_quadContext.IndexCount += INDICES_PER_QUAD;
		++m_stats.TotalQuads;
	}

	void Renderer::DrawQuad(const QuadRenderData& data)
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

		SetupVertices(&m_quadContext.CurrentVertex, data.Transform, data.Color, textureCoords, 0.f);

		m_quadContext.IndexCount += INDICES_PER_QUAD;
		++m_stats.TotalQuads;
	}




	void Renderer::BeginFrame()
	{
		/* Set current vertex to point to the first element */
		m_quadContext.CurrentVertex = m_quadContext.Buffer;
		m_quadContext.IndexCount = 0;
		m_textureSlotIndex = 1;
	}

	void Renderer::Display()
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
		m_quadContext.GLSLShader->Activate();	// Fetch instead from ResourceHolder??

		/* Set view-projection matrix */
		//glm::mat4 viewProjection = m_camera->GetViewProjectionMatrix();
		// m_quadContext.GLSLShader->SetMatrix4("uViewProjection", viewProjection);
		
		glBindVertexArray(m_quadContext.VAO);
		glDrawElements(GL_TRIANGLES, m_quadContext.IndexCount, GL_UNSIGNED_INT, nullptr);

		++m_stats.TotalDraws;

		//DisplayQuads();
		// DisplayText();
	}

	void Renderer::EndFrame()
	{
		Display();

		// Reset stats
		m_stats.TotalDraws = 0;
		m_stats.TotalQuads = 0;
	}
	
	void Renderer::SetProjectionMatrix(const glm::mat4& natrix)
	{
		m_quadContext.GLSLShader->SetMatrix4("uViewProjection", natrix);
	}

	void Renderer::SetShader(GLSLShader* shader)
	{
		m_quadContext.GLSLShader = shader;
		m_quadContext.GLSLShader->Activate();

		int samplers[32];
		for (int i = 0; i < 32; ++i)
			samplers[i] = i;

		m_quadContext.GLSLShader->SetIntArray("uTextures", samplers, 32);

		// set view projection here as well??
	}

	//void Renderer::SetCamera(Camera* aCamera)
	//{
	//	m_camera = aCamera;
	//}
	
	bool Renderer::IsTextureBound(unsigned texID, float& outTexIndex)
	{
		for (uint32_t i = 1; i < m_textureSlotIndex; ++i)
		{
			if (m_textureSlots[i] == texID)
			{
				outTexIndex = (float)i;
				return true;
			}
		}
		return false;
	}

	void Renderer::DisplayQuads()
	{
		
	}

	void Renderer::DisplayText()
	{
		//auto* shader = m_textContext.GLSLShader;

		//shader->Activate();
		//shader->SetVector4f("uText Color", { 1.f, 1.f, 1.f, 1.f }); // TODO; fix color...

		//glm::mat4 projection = m_camera->GetProjectionMatrix();
		//shader->SetMatrix4("uProjection", projection);

		//glActiveTexture(GL_TEXTURE0); // ????????????????????
		//glBindVertexArray(m_textContext.VAO);

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