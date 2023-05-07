#include "Pch.h"
#include "SpriteRenderer.h"
#include "Rendering/Shader/Shader.h"
#include "Rendering/Texture/Texture2D.h"
#include "Data/Structs.h"


#include "Resources/ResourceHolder.hpp"

#include "Core/Rendering/Camera/Camera.h"

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

		// glUseProgram(m_shader->GetRendererID());
		m_shader->Activate();
		// auto location = glGetUniformLocation(m_shader->GetRendererID(), "u_Textures");
		int samplers[2] = { 0, 1 };	// for two textures (can handle up to 30??)
		m_shader->SetInts("u_Textures", 2, samplers);

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

	void SpriteRenderer::SetCamera(Camera* aCamera)
	{
		m_camera = aCamera;
	}

	void SpriteRenderer::ConfigureShader()
	{
		/* Tell OpenGL which texture unit the shader sampler belongs to */
		m_shader->Activate();
		m_shader->SetInt("Texture", 0); 


		float SCR_WIDTH = 1400;
		float SCR_HEIGHT = 800;

		auto projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f); // Determined by camera??
		m_shader->SetMatrix4("projection", projection);

		//glm::mat4 projection = glm::ortho(0.0f, (float)aWidth, (float)aHeight, 0.0f, -1.0f, 1.0f);
		//glm::mat4 projection = glm::perspective(glm::radians(45.0f), ());

		//ResourceHolder<Shader>::GetInstance().GetResource("Sprite").SetInt("image", 0);
		//ResourceHolder<Shader>::GetInstance().GetResource("Sprite").SetMatrix4("projection", projection);
	}

	void SpriteRenderer::Render(const SpriteRenderData& someData) // TODO: Accept texture as pointer => check if nullptr...
	{
		assert(m_shader && "ERROR; Shader is not set!");

		m_shader->Activate();


		// glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

		// Have as members?
		glm::mat4 model			= glm::mat4(1.f);
		//glm::mat4 view			= glm::mat4(1.f); 
		//glm::mat4 projection	= glm::mat4(1.f);

		

		// TODO; Size...

		model = glm::rotate(model, glm::radians(someData.m_rotation), glm::vec3(1.f, 0.f, 0.f));	// last is rotation angle (pass in data?)
		//model = glm::rotate(model, glm::radians(someData.m_rotation), glm::vec3(0.f, 0.f, 1.f));	// last is rotation angle (pass in data?)


		// TEST
		model = glm::scale(model, glm::vec3(someData.m_size.x, someData.m_size.y, someData.m_size.z));
		model = glm::translate(model, glm::vec3(someData.m_position.x, someData.m_position.y, someData.m_position.z));


		//view = glm::translate(view, glm::vec3(0.f, 0.f, -3.0f));	// Position?
		//projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

		if (m_camera)
		{
			const auto& attrib = m_camera->m_attributes;
			glm::vec3 position	= { attrib.m_position.x,	attrib.m_position.y,	attrib.m_position.z };
			glm::vec3 front		= { attrib.m_front.x,		attrib.m_front.y,		attrib.m_front.z };
			glm::vec3 up		= { attrib.m_up.x,			attrib.m_up.y,			attrib.m_up.z };

			glm::mat4 view = glm::lookAt(position, position + front, up );	
			m_shader->SetMatrix4("view", view);
		}


		m_shader->SetMatrix4("model", model);

		// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
		//m_shader->SetMatrix4("projection", projection); 

		m_shader->SetVector4f("Color", someData.m_color);

		/* Bind Texutre */
		glActiveTexture(GL_TEXTURE0);
		someData.m_texture.Bind();

		/* Draw */
		glBindVertexArray(m_quadVAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		glBindVertexArray(0);
	}









	void SpriteRenderer::InitBatch()
	{
		float vertices[] =
		{
			// positions				// colors  				// Texture coord		// Text ID
			-1.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f, 1.0f,		0.f, 0.f,				0.f,
			-0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f, 1.0f,		1.f, 0.f,				0.f,
			-0.5f,  0.5f, 0.0f,		0.0f, 0.0f, 1.0f, 1.0f,		1.f, 1.f,				0.f,
			-1.5f,  0.5f, 0.0f,		1.0f, 1.0f, 0.0f, 1.0f,		0.f, 1.f,				0.f,

			 0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f, 1.0f,		0.f, 0.f,				1.f,
			 1.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f, 1.0f,		1.f, 0.f,				1.f,
			 1.5f,  0.5f, 0.0f,		0.0f, 0.0f, 1.0f, 1.0f,		1.f, 1.f,				1.f,
			 0.5f,  0.5f, 0.0f,		1.0f, 1.0f, 0.0f, 1.0f,		0.f, 1.f,				1.f
		};

		unsigned indices[] =
		{
			0, 1, 2, 2, 3, 0,
			4, 5, 6, 6, 7, 4
			//0, 1, 3,
			//1, 2, 3,
		};

		unsigned VBO;
		glGenVertexArrays(1, &m_batchQuadVAO);
		glBindVertexArray(m_batchQuadVAO);

		/* Create vertex buffer object */
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		/* Create Element array */
		//glGenBuffers(1, &EBO);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		/* Specify layout of the vertex data */

		/* Position Attribute */
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)0);

		/* Color Attribute */
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(3 * sizeof(float)));
		
		/* Texture Coord Attribute */
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(7 * sizeof(float)));


		/* Texture ID Attribute */
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(9 * sizeof(float)));


		/* Unbind VBO and VAO */
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);



		// Bind texture to sloths...


		// To render => bind glBindTextureUnit(0, m_texture); to render sloth 0??
	}

	void SpriteRenderer::RenderBatch()
	{
		assert(m_shader && "ERROR; Shader is not set!");

		ResourceHolder<Shader>::GetInstance().GetResource("Batched_Sprite").Activate();

		// m_shader->Activate();


		// glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

		// Have as members?
		glm::mat4 model = glm::mat4(1.f);
		//glm::mat4 view			= glm::mat4(1.f); 
		//glm::mat4 projection	= glm::mat4(1.f);



		// TODO; Size...

		// model = glm::rotate(model, glm::radians(someData.m_rotation), glm::vec3(1.f, 0.f, 0.f));	// last is rotation angle (pass in data?)
		

		// TEST
		model = glm::scale(model, glm::vec3(1.f, 1.f, 1.f));
		//model = glm::translate(model, glm::vec3(someData.m_position.x, someData.m_position.y, someData.m_position.z));


		//view = glm::translate(view, glm::vec3(0.f, 0.f, -3.0f));	// Position?
		//projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

		if (m_camera)
		{
			const auto& attrib = m_camera->m_attributes;
			glm::vec3 position = { attrib.m_position.x,	attrib.m_position.y,	attrib.m_position.z };
			glm::vec3 front = { attrib.m_front.x,		attrib.m_front.y,		attrib.m_front.z };
			glm::vec3 up = { attrib.m_up.x,			attrib.m_up.y,			attrib.m_up.z };

			glm::mat4 view = glm::lookAt(position, position + front, up);
			m_shader->SetMatrix4("view", view);
		}


		m_shader->SetMatrix4("model", model);

		// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
		//m_shader->SetMatrix4("projection", projection); 

		m_shader->SetVector4f("Color", someData.m_color);

		/* Bind Texutre */
		glActiveTexture(GL_TEXTURE0);
		someData.m_texture.Bind();

		/* Draw */
		glBindVertexArray(m_quadVAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
	}





	void SpriteRenderer::RenderInstanced(const std::vector<CU::Vector3<float>> somePositions)
	{
		// glDrawElementsInstanced(); // also takes an instance count (number of instances we want to render)
	}


}