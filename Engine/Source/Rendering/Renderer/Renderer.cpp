#include "Pch.h"
#include "Renderer.h"
#include "../Material/Material.h"
#include "../Texture/Texture2D.h"
#include "../Texture/Subtexture2D.h"
#include "../Camera/Camera.h" // TEMP..
#include "../Shader/Shader.h"
#include "glm.hpp"
#include "Resources/ResourceHolder.h"
#include "Platform/Window/Window.h"

#define INDICES_PER_QUAD 6
#define VERTICES_PER_QUAD 4

constexpr size_t MaxQuadCount = 10000;				// uint32_t instead??
constexpr size_t MaxVertexCount = MaxQuadCount * 4;
constexpr size_t MaxIndexCount = MaxQuadCount * 6;


namespace Hi_Engine
{
	void GenerateIndices(uint32_t* indices)
	{
		uint32_t offset = 0;

		/* Generate all available indices */
		for (auto i = 0; i < MaxIndexCount; i += 6)
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

	Renderer::Renderer(Window& window)
		: m_window{ window }	// : m_buffer{ new Vertex[Constants::maxVertexCount] }, m_currentVertex{ nullptr }
	{
		//m_quadContext.Buffer = new Vertex[Constants::MaxVertexCount];

	
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

		for (auto i = 1; i < MaxTextureSlots; ++i)
			m_textureSlots[i] = 0;
	}

	Renderer::~Renderer()
	{
	}

	bool Renderer::Initialize()
	{
		GLenum error = glewInit();
		if (error != GLEW_OK)
		{
			std::cerr << "GLEW Error: " << glewGetErrorString(error) << std::endl;
			return false;
		}

		/* Configure render states */
		glEnable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		return true;
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

	void Renderer::Deserialize(const rapidjson::Value& json)
	{
		auto renderer = json["renderer"].GetObj();

		int vertexMaxCount = renderer["max_count"]["vertex"].GetInt();
		m_quadContext.Buffer = new Vertex[vertexMaxCount];

		SetupVertexArray();

		std::string res = renderer["default_shader"].GetString();
		auto shader = ResourceHolder<GLSLShader>::GetInstance().GetResource(res);

		SetShader(shader.get());
	}

	void Renderer::SetProjectionMatrix(const glm::mat4& proj)
	{
		if (auto* shader = m_quadContext.GLSLShader)
		{
			shader->SetMatrix4("uViewProjection", proj);
		}
		else
		{
			Logger::LogWarning("Renderer::SetProjectionMatrix - No Shader set!");
		}
	}

	void Renderer::AddSpriteBatch(SpriteBatch&& batch)
	{
		m_spriteBatches.push(std::move(batch));
	}

	void Renderer::BeginFrame()
	{
		// Reset stats
		m_stats.TotalDraws = 0;
		m_stats.TotalQuads = 0;
	}

	void Renderer::ProcessBatches()
	{
		BeginNewBatch();

		while (!m_spriteBatches.empty())
		{
			auto batch = m_spriteBatches.front();

			for (const auto& sprite : batch.Sprites)
			{
				DrawSprite(sprite);
			}

			m_spriteBatches.pop();
		}

		Display();
	}

	void Renderer::EndFrame()
	{
		Display();

		// std::cout << "Total draws: " << m_stats.TotalDraws << ", total quads: " << m_stats.TotalQuads << "\n";

		m_window.SwapBuffers();

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
		//m_quadContext.GLSLShader->Activate();

		
		glBindVertexArray(m_quadContext.VAO);
		glDrawElements(GL_TRIANGLES, m_quadContext.IndexCount, GL_UNSIGNED_INT, nullptr);

		++m_stats.TotalDraws;
	}


	void Renderer::DrawSprite(const Sprite& sprite)
	{
		auto* subtexture = sprite.Subtexture;

		if (!subtexture) // TODO; use some "invalid" texture instead
			return;

		// unsigned textureId = subtexture->GetTexture().GetID();  // Dont use weak??

		unsigned textureID = sprite.Subtexture->GetTexture().GetID();
		float textureIndex = 0;

		/* Check if this texture is already bound to a slot */
		if (!IsTextureBound(textureID, textureIndex))
		{
			textureIndex = (float)m_textureSlotIndex;
			m_textureSlots[m_textureSlotIndex] = textureID;

			++m_textureSlotIndex;
		}

		if (m_quadContext.IndexCount >= MaxIndexCount)
		{
			Display();
			BeginNewBatch();
		}

		SetupVertices(&m_quadContext.CurrentVertex, sprite.Transform, sprite.Color, subtexture->GetTexCoords(), textureIndex);

		m_quadContext.IndexCount += INDICES_PER_QUAD;
		++m_stats.TotalQuads;
	}

	void Renderer::DrawQuad(const QuadRenderData& data)
	{
		// Check if buffer is full
		if (m_quadContext.IndexCount >= MaxIndexCount)
		{
			Display();
			BeginNewBatch();
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

	void Renderer::SetShader(GLSLShader* shader)
	{
		m_quadContext.GLSLShader = shader;
		m_quadContext.GLSLShader->Activate();

		int samplers[32];
		for (int i = 0; i < 32; ++i)
			samplers[i] = i;

		m_quadContext.GLSLShader->SetIntArray("uTextures", samplers, 32);
	}

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

	void Renderer::ClearScreen()
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::SetupVertexArray()
	{
		/* Create vertex array object */
		glGenVertexArrays(1, &m_quadContext.VAO);
		glBindVertexArray(m_quadContext.VAO);

		/* Create vertex buffer object */
		glGenBuffers(1, &m_quadContext.VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_quadContext.VBO);
		glBufferData(GL_ARRAY_BUFFER, MaxVertexCount * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

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
		uint32_t indices[MaxIndexCount];
		GenerateIndices(indices);

		/* Create element buffer object */
		glCreateBuffers(1, &m_quadContext.EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_quadContext.EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		/* Unbind VBO and VAO */
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void Renderer::BeginNewBatch()
	{
		/* Set current vertex to point to the first element */
		m_quadContext.CurrentVertex = m_quadContext.Buffer;
		m_quadContext.IndexCount = 0;
		m_textureSlotIndex = 1;
	}
}