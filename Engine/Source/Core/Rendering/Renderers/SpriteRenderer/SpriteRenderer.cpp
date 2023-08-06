#include "Pch.h"
#include "SpriteRenderer.h"
#include "Data/Structs.h"
#include "Rendering/Material/Material.h"
#include "Rendering/Shader/Shader.h"
#include "Rendering/Camera/Camera.h"
#include "Rendering/Texture/Texture2D.h"


namespace Hi_Engine
{
	SpriteRenderer::SpriteRenderer()
		: m_camera{ nullptr }, m_windowSize{ 1400, 800 }, m_VAO{ 0 }
	{
	}

	SpriteRenderer::~SpriteRenderer()
	{
	}

	SpriteRenderer& SpriteRenderer::GetInstance()
	{
		static SpriteRenderer instance;
		return instance;
	}

	void SpriteRenderer::Init()
	{
		float vertices[] =
		{
			// positions             // texture coords
			 0.5f,  0.5f, 0.0f,      1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f,      1.0f, 0.0f,
			-0.5f, -0.5f, 0.0f,      0.0f, 0.0f,
			-0.5f,  0.5f, 0.0f,      0.0f, 1.0f
		};

		unsigned indices[] =
		{
			0, 2, 1,
			0, 3, 2

			//0, 1, 2,
			//2, 3, 0

			//0, 1, 3,
			//1, 2, 3
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
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

		/* Texture Coord Attribute */
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

		/* Unbind VBO and VAO */
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	
	void SpriteRenderer::Shutdown()
	{
		// TODO; delete...
	}

	void SpriteRenderer::Render(const SpriteRenderData& someData)
	{
		auto* shader = someData.Material->GetShader();
		auto* texture = someData.Material->GetTexture();

		assert(m_camera && shader && texture && "Failed to render!");

		shader->Activate();
		shader->SetInt("uTexture", 0);	// Maybe??

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

		/* Bind Texutre */
		glActiveTexture(GL_TEXTURE0);				// possible to do in Texture??
		texture->Bind();

		/* Draw */
		glBindVertexArray(m_VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
	}

	void SpriteRenderer::SetCamera(Camera* aCamera)
	{
		m_camera = aCamera;
	}
}