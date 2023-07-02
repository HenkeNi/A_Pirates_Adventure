#include "Pch.h"
#include "PrimitiveRenderer.h"
#include "Rendering/Camera/Camera.h"
#include "Rendering/Shader/Shader.h"
#include "Data/Structs.h"


namespace Hi_Engine
{
	PrimitiveRenderer::PrimitiveRenderer()
		: m_camera{ nullptr }, m_windowSize{ 1400, 800 }, m_VAO{ 0 }
	{
	}

	PrimitiveRenderer::~PrimitiveRenderer()
	{
	}

	PrimitiveRenderer& PrimitiveRenderer::GetInstance()
	{
		static PrimitiveRenderer instance;
		return instance;
	}
	
	void PrimitiveRenderer::Init()
	{
		float vertices[] =
		{
			// positions			// colors
			 0.5f,  0.5f, 0.f,		1.f, 1.f, 1.f,
			 0.5f, -0.5f, 0.f,		1.f, 1.f, 1.f,
			-0.5f, -0.5f, 0.f,		1.f, 1.f, 1.f,
			-0.5f,  0.5f, 0.f,		1.f, 1.f, 1.f,
		};

		unsigned indices[] =
		{
			0, 2, 1,
			0, 3, 2
		};

		unsigned VBO, EBO;
		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		/* Create vertex buffer object */
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		/* Create Element array */
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		/* Specify layout of the vertex data */

		/* Position Attribute */
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

		/* Texture Coord Attribute */
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

		/* Unbind VBO and VAO */
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void PrimitiveRenderer::Shutdown()
	{
	}
	
	void PrimitiveRenderer::Render(const PrimitiveRenderData& someData)
	{
		auto* shader = someData.m_shader;

		assert(m_camera && shader && "Failed to render!");

		shader->Activate();

		/* Set projection matrix */
		glm::mat4 projection = glm::perspective(glm::radians(m_camera->GetZoom()), (float)m_windowSize.x / (float)m_windowSize.y, 0.1f, 100.0f); // Todo; get projection form camera?
		shader->SetMatrix4("uProjection", projection);

		/* Set view matrix */
		glm::mat4 view = m_camera->GetViewMatrix();
		shader->SetMatrix4("uView", view);

		/* Set model matrix */
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(someData.Position));
		model = glm::rotate(model, glm::radians(someData.Rotation), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(someData.Scale, 1.0f));
		shader->SetMatrix4("uModel", model);


		/* Draw */
		glBindVertexArray(m_VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
	}

	void PrimitiveRenderer::SetCamera(Camera* aCamera)
	{
		m_camera = aCamera;
	}
}