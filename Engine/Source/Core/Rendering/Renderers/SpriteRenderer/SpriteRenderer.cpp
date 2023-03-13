#include "Pch.h"
#include "SpriteRenderer.h"
#include "Rendering/Shader/Shader.h"
#include "Rendering/Texture/Texture2D.h"
#include "Data/Structs.h"


#include "Resources/ResourceHolder.hpp"

namespace Hi_Engine
{
	SpriteRenderer::SpriteRenderer()
		: m_shader{ nullptr }, m_quadVAO{ 0 }
	{
	}

	SpriteRenderer::~SpriteRenderer()
	{
		glDeleteVertexArrays(1, &m_quadVAO);
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
			0, 1, 3,
			1, 2, 3
		};

		unsigned VBO, EBO;
		glGenVertexArrays(1, &m_quadVAO);
		glBindVertexArray(m_quadVAO);

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

	void SpriteRenderer::SetShader(Shader* aShader)
	{
		assert(aShader && "Shader was nullptr!");
		m_shader = aShader;

		ConfigureShader();
	}

	void SpriteRenderer::ConfigureShader()
	{
		/* Tell OpenGL which texture unit the shader sampler belongs to */
		m_shader->Activate();
		m_shader->SetInt("Texture", 0); 



		//glm::mat4 projection = glm::ortho(0.0f, (float)aWidth, (float)aHeight, 0.0f, -1.0f, 1.0f);
		//glm::mat4 projection = glm::perspective(glm::radians(45.0f), ());

		//ResourceHolder<Shader>::GetInstance().GetResource("Sprite").SetInt("image", 0);
		//ResourceHolder<Shader>::GetInstance().GetResource("Sprite").SetMatrix4("projection", projection);
	}

	void SpriteRenderer::Render(const SpriteRenderData& someData)
	{
		assert(m_shader && "ERROR; Shader is not set!");

		m_shader->Activate();

		// Have as members?
		glm::mat4 model			= glm::mat4(1.f);
		glm::mat4 view			= glm::mat4(1.f); 
		glm::mat4 projection	= glm::mat4(1.f);

		float SCR_WIDTH = 1400;
		float SCR_HEIGHT = 800;

		model = glm::rotate(model, glm::radians(someData.m_rotation), glm::vec3(0.f, 0.f, 1.f));	// last is rotation angle (pass in data?)
		view = glm::translate(view, glm::vec3(0.f, 0.f, -3.0f));	// Position?
		projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

		m_shader->SetMatrix4("model", model);
		m_shader->SetMatrix4("view", view);

		// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
		m_shader->SetMatrix4("projection", projection); 

		m_shader->SetVector4f("Color", someData.m_color);

		/* Bind Texutre */
		glActiveTexture(GL_TEXTURE0);
		someData.m_texture.Bind();

		/* Draw */
		glBindVertexArray(m_quadVAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		glBindVertexArray(0);
	}
}