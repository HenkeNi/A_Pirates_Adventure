#include "Pch.h"
#include "Renderer.h"
#include "Data/Constants.h"
#include "../Material/Material.h"

#include "../Camera/Camera.h" // TEMP..
#include "../Window/Window.h"


namespace Hi_Engine
{
	void GenerateIndices(uint32_t* someIndices)
	{
		uint32_t offset = 0;

		/* Generate all available indices */
		for (auto i = 0; i < Constants::maxIndexCount; i += 6)
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

	Renderer::Renderer()
		: m_buffer{ new Vertex[Constants::maxVertexCount] }, m_currentVertex{ nullptr }
	{
		Dispatcher::GetInstance().Subscribe(this);



		///* Configure render states */
		//glEnable(GL_DEPTH_TEST);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glEnable(GL_BLEND);

		quadVertexPositions[0] = { -0.5f, -0.5f, 0.f, 1.f };
		quadVertexPositions[1] = {  0.5f, -0.5f, 0.f, 1.f };
		quadVertexPositions[2] = {  0.5f,  0.5f, 0.f, 1.f };
		quadVertexPositions[3] = { -0.5f,  0.5f, 0.f, 1.f };

		quadTexturePositions[0] = { 0.f, 0.f };
		quadTexturePositions[1] = { 1.f, 0.f };
		quadTexturePositions[2] = { 1.f, 1.f };
		quadTexturePositions[3] = { 0.f, 1.f };

		// Temp
		m_camera = new Camera; // pass in camera? or keep in Engine (pass event for camera set)



		// DO this in init? or elsewhere?
		//glCreateTextures(GL_TEXTURE_2D, 1, &m_whiteTexture);
		//glGenTextures(GL_TEXTURE_2D, &m_whiteTexture);
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

		for (auto i = 1; i < Constants::maxTextureSlots; ++i)
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
			if (command.m_type == eRenderCommandType::DrawSprite)
			{
				auto data = command.m_spriteRenderData;

				auto id = data.Material->GetTexture()->GetID();
				//DrawQuad(data.Position, data.Scale, 1.f, data.Rotation);
				DrawQuad(data.Position, data.Scale, data.Material->GetTexture()->GetID(), data.Rotation);
			}
			else if (command.m_type == eRenderCommandType::SetShader)
			{
				m_activeShader = command.m_shader;
			}
			else if (command.m_type == eRenderCommandType::SetCamera)
			{
				m_camera = command.m_camera;
			}

			commands.pop();
		}
	}

	void Renderer::Init(Window* aTarget)
	{
		m_target = aTarget;

		/* Create vertex array object */
		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		/* Create vertex buffer object */
		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, Constants::maxVertexCount * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

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
		uint32_t indices[Constants::maxIndexCount];
		GenerateIndices(indices);

		/* Create element buffer object */
		glCreateBuffers(1, &m_EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		/* Unbind VBO and VAO */
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void Renderer::Shutdown()
	{
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);
		glDeleteBuffers(1, &m_EBO);

		// Todo; Delete texture ??
		glDeleteTextures(1, &m_whiteTexture); // MOVE later?

		delete[] m_buffer;
	}

	void Renderer::Reset()
	{
		/* Set current vertex to point to the first element */
		m_currentVertex = m_buffer; 

		m_indexCount = 0;
		m_textureSlotIndex = 1;

		// ResetStats()?
	}

	//void Renderer::EndFrame()
	//{
	//	//GLsizeiptr size = (m_currentBufferIndex + 1) * sizeof(Vertex);
	//
	//	/* Pass data to the buffer (VBO) */
	//	GLsizeiptr size = (uint8_t*)m_currentVertex - (uint8_t*)m_buffer;
	//	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	//	glBufferSubData(GL_ARRAY_BUFFER, 0, size, m_buffer);
	//}

	void Renderer::Display()
	{
		/* Pass data to the buffer (VBO) */
		GLsizeiptr size = (uint8_t*)m_currentVertex - (uint8_t*)m_buffer;
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, m_buffer);

		/* Actual draw call */
		for (uint32_t i = 0; i < m_textureSlotIndex; ++i)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, m_textureSlots[i]);

			//glBindTextureUnit(i, m_textureSlots[i]);		// 2 bind to arra position 1 and 1 to array positoin 2
		}

		// But index works in shader as a array position... (wrong?!)





		// auto& shader = ResourceHolder<Shader>::GetInstance().GetResource("sprite_batch");
		m_activeShader->Activate();



		// texture.Bind();	// Take in texture unit??

		//int samplers[2] = { 0, 1 };
		//shader.SetIntArray("uTextures", samplers, 2);	// Maybe??
		// list from 0 to maximum texture sloths ()

		// test
		// m_activeShader->SetIntArray("uTextures", m_textureSlots, m_textureSlotIndex);


		// TODO; make camera return either both a projection and a view matrix, or a viewprojectin matrix

		/* Set projection matrix */
		glm::mat4 projection = m_camera->GetProjectionMatrix();
		//auto windowSize = m_target->GetSize();
		//glm::mat4 projection = glm::perspective(glm::radians(m_camera->GetZoom()), (float)windowSize.x / (float)windowSize.y, 0.1f, 100.0f); // Todo; get projection form camera?
		m_activeShader->SetMatrix4("uProjection", projection);	// TODO; get this data from window?   TODOD; CAmare.>GetViewProejctioNatrx()

		/* Set view matrix */
		glm::mat4 view = m_camera->GetViewMatrix();
		m_activeShader->SetMatrix4("uView", view);

		glBindVertexArray(m_VAO);
		glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, nullptr);
		
		++m_drawCount;

		// MOVE to Reset..?
	}

	void Renderer::DrawQuad(const glm::vec3& aPosition, const glm::vec2& aSize, const glm::vec4& aColor)
	{
		if (IsBufferFull())
		{
			Display();
			Reset();
		}

		float textureIndex = 0.f;
		
		SetupVertices(&m_currentVertex, aPosition, aSize, aColor, textureIndex);	// Rename?? CrateQuad --- push back quad to buffer

		// TODO; multiply with rotation matrix? here. since cant do it in shader..?

		m_indexCount += 6;	// Vertices per quad (use #definee instead??
		++m_quadCount;			// NEEDED??
	}

	void Renderer::DrawQuad(const glm::vec3& aPosition, const glm::vec2& aSize, uint32_t aTextureID, float aRotation)
	{
		if (IsBufferFull() || m_textureSlotIndex > 31)
		{
			Display();
			Reset();
		}

		constexpr glm::vec4 color = { 1.f, 1.f, 1.f, 1.f };
		
		float textureIndex = 0.f;
		
		// Create function bool IsTexutreBound(textreIndex, &outIndex)
		// check if this texture has already been used...
		for (uint32_t i = 1; i < m_textureSlotIndex; ++i)
		{
			if (m_textureSlots[i] == aTextureID)
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.f)
		{
			textureIndex = (float)m_textureSlotIndex;
			m_textureSlots[m_textureSlotIndex] = aTextureID;
 			++m_textureSlotIndex;
		}

		SetupVertices(&m_currentVertex, aPosition, aSize, color, textureIndex, aRotation);

		m_indexCount += 6;
		++m_quadCount;
	}

	void Renderer::SetShader(Shader* aShader)
	{
		m_activeShader = aShader;
		m_activeShader->Activate();

		int samplers[32];
		for (int i = 0; i < 32; ++i)
			samplers[i] = i;

		m_activeShader->SetIntArray("uTextures", samplers, 32);
	}

	void Renderer::SetCamera(Camera* aCamera)
	{
		m_camera = aCamera;
	}

	// TOOD; change aSize to a scale!?
	void Renderer::SetupVertices(Vertex** aTarget, const glm::vec3& aPosition, const glm::vec2& aSize, const glm::vec4& aColor, float aTexIndex, float aRotation)
	{
		static const unsigned quadVertices = 4;

		glm::vec3 rotationAxis = { 1.f, 0.f, 0.f };


		// TEMP - render part of texture 
		float xPos = 2, yPos = 3; // sheet coordinate
		float sheetWidth = 2560.f, sheetHeight = 1664.f; // use texture.get width and getHeight()
		float spriteWidth = 128.f, spriteHeight = 128.f;

		glm::vec2 textureCoords[] = {
			{ (xPos * spriteWidth) / sheetWidth		 , (yPos * spriteHeight) / sheetHeight },
			{ ((xPos + 1) * spriteWidth) / sheetWidth, (yPos * spriteHeight) / sheetHeight },
			{ ((xPos + 1) * spriteWidth) / sheetWidth, ((yPos + 1) * spriteHeight) / sheetHeight },
			{ (xPos * spriteWidth) / sheetWidth		 , ((yPos + 1)* spriteHeight) / sheetHeight },
		};

		// END TEMP 


		// Create a transformation matrix
		glm::mat4 transform = glm::mat4(1.f);
		transform = glm::translate(transform, glm::vec3(aPosition.x, aPosition.y, aPosition.z));
		transform = glm::rotate(transform, glm::radians(aRotation), rotationAxis);
		//transform = glm::rotate(transform, glm::radians(aRotation), rotationAxis);
		transform = glm::scale(transform, glm::vec3(aSize.x, aSize.y, 1.0f));

		for (int i = 0; i < quadVertices; ++i)
		{
			(*aTarget)->Position = transform * quadVertexPositions[i];
			(*aTarget)->Color = aColor;
			(*aTarget)->TexCoords = quadTexturePositions[i];	// use textureCoords instead...  
			(*aTarget)->TexIndex = aTexIndex + 0.1f; // (aTexIndex / 10);	// small hack; makes it 1.1 instead of 1.0 (shader error when converting it to an int)
			++(*aTarget);
		}
	}

	bool Renderer::IsBufferFull() const
	{
		return m_indexCount >= Constants::maxIndexCount;
	}	
}