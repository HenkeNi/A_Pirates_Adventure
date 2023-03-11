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

		unsigned VBO, EBO;						// TODO: Store as members and delete later?
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


		// HOW TO RENDER COLORS?? => Set uniform?

		//glm::mat4 model			= glm::mat4(1.f);
		//glm::mat4 view			= glm::mat4(1.f);
		//glm::mat4 projection	= glm::mat4(1.f);
		//model = glm::rotate(model, glm::radians(someData.m_rotation), glm::vec3(1.f, 0.f, 0.f));
		//view = glm::translate(view, glm::vec3(0.f, 0.f, -3.f));
		//projection = glm::perspective(glm::radians(45.0f), (float)1400 / (float)800, 0.1f, 100.0f);

		m_shader->SetVector4f("Color", someData.m_color);

		//m_shader->SetMatrix4("model", model);
		//m_shader->SetMatrix4("view", view);
		//m_shader->SetMatrix4("projection", projection);

		/* Bind Texutre */
		glActiveTexture(GL_TEXTURE0);
		someData.m_texture.Bind();

		glBindVertexArray(m_quadVAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// pass them to the shaders (3 different ways)
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
		// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.

		// render container
		//glBindVertexArray(VAO);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		////model = glm::translate(model, glm::vec3(someData.m_position.x, someData.m_position.y, 0.f)); // Use own math library!?
		//model = glm::translate(model, glm::vec3(someData.m_position.x, someData.m_position.y, someData.m_position.z)); // Use own math library!?

		//model = glm::translate(model, glm::vec3(0.5f * someData.m_size.x, 0.5f * someData.m_size.y, 0.5f * someData.m_position.z));
		//model = glm::rotate(model, glm::radians(someData.m_rotation), glm::vec3(0.f, 0.f, 1.f));
		//model = glm::translate(model, glm::vec3(-0.5f * someData.m_size.x, -0.5f * someData.m_size.y, -0.5f * someData.m_position.z));

		//model = glm::scale(model, glm::vec3(someData.m_size.x, someData.m_size.y, 1.f));

		//m_shader->SetMatrix4("model", model);
		//m_shader->SetVector4f("spriteColor", someData.m_color);

		//glActiveTexture(GL_TEXTURE0);
		//someData.m_texture.Bind();

		//glBindVertexArray(m_quadVAO);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glBindVertexArray(0);
	}



}