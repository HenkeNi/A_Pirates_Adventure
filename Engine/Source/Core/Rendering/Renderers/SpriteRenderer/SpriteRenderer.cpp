#include "Pch.h"
#include "SpriteRenderer.h"
#include "Rendering/Shader/Shader.h"
#include "Rendering/Texture/Texture2D.h"
#include "Data/Structs.h"


#include "Messaging/Events/RenderEvents/RenderEvents.h"

#include "Resources/ResourceHolder.hpp"
#include "../../Material/Material.h"
#include "Core/Rendering/Camera/Camera.h"
#include "Core/Rendering/Camera/OrthographicCamera.h"
#include "Messaging/Dispatcher/Dispatcher.h"
namespace Hi_Engine
{
	//const size_t SpriteRenderer::s_maxNumberOfQuads = 1000;

	//const size_t SpriteRenderer::s_maxVertexCount = s_maxQuadAmount * 4;
	//const size_t SpriteRenderer::s_maxIndexCount = s_maxQuadAmount * 6;	
	//const size_t SpriteRenderer::s_maxTexturesCount = 32;


	SpriteRenderer::SpriteRenderer()
		//: /*m_quadBuffer{ new Vertex[s_maxVertexCount] },*/ /*m_shader{ nullptr }*/ //m_quadVAO{ 0 }
	{
		Dispatcher::GetInstance().Subscribe(this);
	}

	SpriteRenderer::~SpriteRenderer()
	{
		glDeleteVertexArrays(1, &m_VAOs["Quad"]);
	}

	SpriteRenderer& SpriteRenderer::GetInstance()
	{
		static SpriteRenderer instance;
		return instance;
	}


	void SpriteRenderer::HandleEvent(RenderSpriteEvent& anEvent)
	{
		Render(anEvent.GetRenderData());
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

		m_VAOs.insert({ "Quad", 0 });

		unsigned VBO, EBO;
		glGenVertexArrays(1, &m_VAOs["Quad"]);
		glBindVertexArray(m_VAOs["Quad"]);

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
		//glDeleteVertexArrays(1, &m_quadVA);
		//glDeleteBuffers(1, &m_quadVB);
		//glDeleteBuffers(1, &m_quadIB);
		//glDeleteTextures(1, &m_rendererData.WhiteTexture);
		//
		//delete[] m_quadBuffer;
	}

	//void SpriteRenderer::BeginRendering()
	//{
	//	// call beign batch??
	//}

	//void SpriteRenderer::EndRendering()
	//{

	//}






	/*void SpriteRenderer::BeginBatch()
	{
		m_currentQuad = m_quadBuffer;
	}

	void SpriteRenderer::EndBatch()
	{
		GLsizeiptr size = (uint8_t*)m_currentQuad - (uint8_t*)m_quadBuffer;
		glBindBuffer(GL_ARRAY_BUFFER, m_quadVB);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, m_quadBuffer);
	}

	void SpriteRenderer::Flush()
	{
		for (uint32_t i = 0; i < m_rendererData.TextureSlotIndex; ++i)
		{
			glBindTextureUnit(i, m_rendererData.TextureSlots[i]);
		}


		glBindVertexArray(m_quadVA);
		glDrawElements(GL_TRIANGLES, m_rendererData.IndexCount, GL_UNSIGNED_INT, nullptr);
		
		m_rendererData.IndexCount = 0;
		m_rendererData.TextureSlotIndex = 1;
	}*/


	//void SpriteRenderer::RenderQuad(const CU::Vector3<float>& aPosition, const CU::Vector3<float>& aSize, const CU::Vector4<float>& aColor)
	//{
	//	// Check if batch is full
	//	if (m_rendererData.IndexCount >= s_maxIndexCount)
	//	{
	//		EndBatch();
	//		Flush();
	//		BeginBatch();
	//	}

	//	float textureIndex = 0.f; // use default/white texture..
	//		
	//	// Vertex 1
	//	m_currentQuad->Position = { aPosition.x, aPosition.y, 0.f };
	//	m_currentQuad->Color = { aColor.x, aColor.y, aColor.z, aColor.w  }; // FIX:.. 
	//	m_currentQuad->TexCoords = { 0.f, 0.f };
	//	m_currentQuad->TexIndex = textureIndex;
	//	++m_currentQuad;

	//	// Vertex 2
	//	m_currentQuad->Position = { aPosition.x + aSize.x, aPosition.y, 0.f };
	//	m_currentQuad->Color = { aColor.x, aColor.y, aColor.z, aColor.w }; // FIX:.. 
	//	m_currentQuad->TexCoords = { 1.f, 0.f };
	//	m_currentQuad->TexIndex = textureIndex;
	//	++m_currentQuad;

	//	// Vertex 3
	//	m_currentQuad->Position = { aPosition.x + aSize.x, aPosition.y + aSize.y, 0.f };
	//	m_currentQuad->Color = { aColor.x, aColor.y, aColor.z, aColor.w }; // FIX:.. 
	//	m_currentQuad->TexCoords = { 1.f, 1.f };
	//	m_currentQuad->TexIndex = textureIndex;
	//	++m_currentQuad;

	//	// Vertex 4
	//	m_currentQuad->Position = { aPosition.x, aPosition.y + aSize.y, 0.f };
	//	m_currentQuad->Color = { aColor.x, aColor.y, aColor.z, aColor.w }; // FIX:.. 
	//	m_currentQuad->TexCoords = { 0.f, 1.f };
	//	m_currentQuad->TexIndex = textureIndex;
	//	++m_currentQuad;

	//}

	//void SpriteRenderer::RenderQuad(const CU::Vector3<float>& aPosition, const CU::Vector3<float>& aSize, uint32_t aTextureID)
	//{
	//	// Check if batch is full
	//	if (m_rendererData.IndexCount >= s_maxIndexCount || m_rendererData.TextureSlotIndex > 31)
	//	{
	//		EndBatch();
	//		Flush();
	//		BeginBatch();
	//	}

	//	constexpr glm::vec4 color = { 1.f, 1.f, 1.f, 1.f };

	//	float textureIndex = 0.f;
	//	for (uint32_t i = 1; i < m_rendererData.TextureSlotIndex; ++i)	// hashmap??
	//	{
	//		if (m_rendererData.TextureSlots[i] == aTextureID)
	//		{
	//			textureIndex = (float)i;
	//			break;
	//		}
	//	}

	//	if (textureIndex == 0.f)
	//	{
	//		textureIndex = (float)m_rendererData.TextureSlotIndex;
	//		m_rendererData.TextureSlots[m_rendererData.TextureSlotIndex] = aTextureID;
	//		++m_rendererData.TextureSlotIndex;
	//	}

	//	// Vertex 1
	//	m_currentQuad->Position = { aPosition.x, aPosition.y, 0.f };
	//	m_currentQuad->Color = color;  
	//	m_currentQuad->TexCoords = { 0.f, 0.f };
	//	m_currentQuad->TexIndex = textureIndex;
	//	++m_currentQuad;

	//	// Vertex 2
	//	m_currentQuad->Position = { aPosition.x + aSize.x, aPosition.y, 0.f };
	//	m_currentQuad->Color = color;  
	//	m_currentQuad->TexCoords = { 1.f, 0.f };
	//	m_currentQuad->TexIndex = textureIndex;
	//	++m_currentQuad;

	//	// Vertex 3
	//	m_currentQuad->Position = { aPosition.x + aSize.x, aPosition.y + aSize.y, 0.f };
	//	m_currentQuad->Color = color;  
	//	m_currentQuad->TexCoords = { 1.f, 1.f };
	//	m_currentQuad->TexIndex = textureIndex;
	//	++m_currentQuad;

	//	// Vertex 4
	//	m_currentQuad->Position = { aPosition.x, aPosition.y + aSize.y, 0.f };
	//	m_currentQuad->Color = color;  
	//	m_currentQuad->TexCoords = { 0.f, 1.f };
	//	m_currentQuad->TexIndex = textureIndex;
	//	++m_currentQuad;
	//}




	void SpriteRenderer::SetShader(Shader* aShader)
	{
		//assert(aShader && "Shader was nullptr!");
		//m_shader = aShader;

		ConfigureShader();
	}

	void SpriteRenderer::SetCamera(Camera* aCamera)
	{
		m_camera = aCamera;
	}

	void SpriteRenderer::ConfigureShader()	// maybe do in material??
	{
		/* Tell OpenGL which texture unit the shader sampler belongs to */
		//m_shader->Activate();
		//m_shader->SetInt("Texture", 0); 


		//float SCR_WIDTH = 1400;
		//float SCR_HEIGHT = 800;

		//auto projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f); // Determined by camera??
		//m_shader->SetMatrix4("projection", projection);

		//glm::mat4 projection = glm::ortho(0.0f, (float)aWidth, (float)aHeight, 0.0f, -1.0f, 1.0f);
		//glm::mat4 projection = glm::perspective(glm::radians(45.0f), ());

		//ResourceHolder<Shader>::GetInstance().GetResource("Sprite").SetInt("image", 0);
		//ResourceHolder<Shader>::GetInstance().GetResource("Sprite").SetMatrix4("projection", projection);
	}

	void SpriteRenderer::Render(const SpriteRenderData& someData) 
	{
		auto* shader = someData.Material->GetShader();

		/* Activate shader */
		shader->Activate();


		// Maybe do in material?
		shader->SetInt("Texture", 0);


		/* Set the model matrix */
		glm::mat4 model = glm::mat4(1.f);
		model = glm::translate(model, glm::vec3(someData.Position));
		model = glm::rotate(model, glm::radians(someData.Rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(someData.Scale, 1.0f));
		shader->SetMatrix4("model", model);

		float SCR_WIDTH = 1400;
		float SCR_HEIGHT = 800;

		/* Set the projection matrix */
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		shader->SetMatrix4("projection", projection);

		/* Bind the texure */
		someData.Material->GetTexture()->Bind();



		//
		//someData.Material->GetShader()->Activate();

		///* Set the projection matrix */
		////someData.Material->GetShader()->SetMatrix4("projection", m_camera->GetMatrices().Projection);

		//const glm::mat4 projection = glm::ortho(0.f, SCR_WIDTH, 0.f, SCR_HEIGHT, -1.f, 1.f); // last two are near and far plane..
		//someData.Material->GetShader()->SetMatrix4("projection", projection);

		///* Set the model matrix */
		//const glm::mat4 model = glm::translate(glm::mat4(1.0f), someData.Position) * glm::rotate(glm::mat4(1.0f), glm::radians(someData.Rotation), glm::vec3(0.0f, 0.0f, 1.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(someData.Scale, 1.0f));
		//someData.Material->GetShader()->SetMatrix4("model", model);

		///* Set the color */
		////someData.Material->GetShader()->SetVector4f("color", someData.Material->GetColor());

		///* Bind the texture */
		//someData.Material->GetTexture()->Bind();

		///* Draw the quad */
		//glBindVertexArray(m_quadVAO);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glBindVertexArray(0);
		//
		//return;




		//assert(m_camera && "ERROR: Camera is not set!");

		///* Activate Shader */
		//someData.Material->GetShader()->Activate();
 
		//glm::mat4 model			= glm::mat4(1.f);
		//model = glm::translate(model, glm::vec3(someData.Position));


		//model = glm::translate(model, glm::vec3(0.5f * someData.Scale.x, 0.5f * someData.Scale.y, 0.0f)); 
		//model = glm::rotate(model, glm::radians(someData.Rotation), glm::vec3(0.0f, 0.0f, 1.0f)); 
		//model = glm::translate(model, glm::vec3(-0.5f * someData.Scale.x, -0.5f * someData.Scale.y, 0.0f)); 

		//model = glm::scale(model, glm::vec3(someData.Scale, 1.f));

		//someData.Material->GetShader()->SetMatrix4("model", model);

		//// TODO; do only once????
		//auto projection = glm::ortho(0.0f, static_cast<float>(SCR_WIDTH), static_cast<float>(SCR_HEIGHT), 0.0f, -1.0f, 1.0f); 
		//someData.Material->GetShader()->SetMatrix4("projection", projection);

		//
		//glm::mat4 view			= glm::mat4(1.f); 
		//glm::mat4 projection	= glm::mat4(1.f);
		// glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

		

		// TODO; Size...

		// model = glm::rotate(model, glm::radians(someData.Rotation), glm::vec3(1.f, 0.f, 0.f));	// last is rotation angle (pass in data?)
		//model = glm::rotate(model, glm::radians(someData.m_rotation), glm::vec3(0.f, 0.f, 1.f));	// last is rotation angle (pass in data?)


		// TEST
		//model = glm::scale(model, glm::vec3({ someData.Scale.x, someData.Scale.y }, 1.f));
		//model = glm::translate(model, glm::vec3(someData.Position.x, someData.Position.y, someData.Position.z));


		//view = glm::translate(view, glm::vec3(0.f, 0.f, -3.0f));	// Position?
		//projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

		/*if (m_camera)
		{
			const auto& attrib = m_camera->m_attributes;
			glm::mat4 view = glm::lookAt(attrib.m_position, attrib.m_position + attrib.m_front, attrib.m_up );
			shader->SetMatrix4("view", view);
		}*/


		//shader->SetMatrix4("model", model);

		// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
		//m_shader->SetMatrix4("projection", projection); 

		//shader->SetVector4f("Color", someData.Material->GetColor());

		/* Bind Texutre */
		glActiveTexture(GL_TEXTURE0);
		someData.Material->GetTexture()->Bind(); 

		/* Draw */
		glBindVertexArray(m_VAOs["Quad"]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		glBindVertexArray(0);
	}









	//void SpriteRenderer::InitBatch()
	//{
	//	// m_rendererData.QuadBuffer = new Vertex[s_maxVertexCount]; // maybe store buffer outside of struct??

	//	/* Create vertex array */
	//	glGenVertexArrays(1, &m_quadVA);
	//	glBindVertexArray(m_quadVA);

	//	/* Create vertex buffer object */
	//	glGenBuffers(1, &m_quadVB);
	//	glBindBuffer(GL_ARRAY_BUFFER, m_quadVB);
	//	glBufferData(GL_ARRAY_BUFFER, s_maxVertexCount * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW); // allocate memory.. 

	//	/* Create Element array */
	//	//glGenBuffers(1, &EBO);
	//	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	//	
	//	/* Specify layout of the vertex data */

	//	/* Position Attribute */
	//	glEnableVertexAttribArray(0);
	//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));

	//	/* Color Attribute */
	//	glEnableVertexAttribArray(1);
	//	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));
	//	
	//	/* Texture Coord Attribute */
	//	glEnableVertexAttribArray(2);
	//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

	//	/* Texture ID Attribute */
	//	glEnableVertexAttribArray(3);
	//	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexIndex));






	//	// make able to handle more than two quads..
	///*	unsigned indices[] =
	//	{
	//		0, 1, 2, 2, 3, 0,
	//		4, 5, 6, 6, 7, 4
	//	};*/

	//	uint32_t indices[s_maxNumberOfQuads];
	//	uint32_t offset = 0;

	//	for (size_t i = 0; i < s_maxIndexCount; i += 6)
	//	{
	//		indices[i + 0] = 0 + offset;
	//		indices[i + 1] = 1 + offset;
	//		indices[i + 2] = 2 + offset;
	//		
	//		indices[i + 3] = 2 + offset;
	//		indices[i + 4] = 3 + offset;
	//		indices[i + 5] = 0 + offset;

	//		offset += 4;
	//	}


	//	glCreateBuffers(1, &m_quadIB);
	//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_quadIB);
	//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);



	//	// 1x1 white texture -> needed??
	//	glCreateTextures(GL_TEXTURE_2D, 1, &m_rendererData.WhiteTexture);
	//	glBindTexture(GL_TEXTURE_2D, m_rendererData.WhiteTexture);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//	uint32_t color = 0xffffffff;
	//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &color);

	//	m_rendererData.TextureSlots[0] = m_rendererData.WhiteTexture;

	//	for (size_t i = 1; i < m_rendererData.MaxTextures; ++i)	// memset?? set to 0...
	//		m_rendererData.TextureSlots[i] = 0;
	//}

	//void SpriteRenderer::RenderBatch(Camera* aCamera, const SpriteRenderData& someData)
	//{
	//	assert(m_shader && "ERROR; Shader is not set!");


	//	// TODO; pass in...
	//	//float vertices[] =
	//	//{
	//	//	// positions				// colors  				// Texture coord		// Text ID
	//	//	-1.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f, 1.0f,		0.f, 0.f,				0.f,
	//	//	-0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f, 1.0f,		1.f, 0.f,				0.f,
	//	//	-0.5f,  0.5f, 0.0f,		0.0f, 0.0f, 1.0f, 1.0f,		1.f, 1.f,				0.f,
	//	//	-1.5f,  0.5f, 0.0f,		1.0f, 1.0f, 0.0f, 1.0f,		0.f, 1.f,				0.f,

	//	//	 0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f, 1.0f,		0.f, 0.f,				1.f,
	//	//	 1.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f, 1.0f,		1.f, 0.f,				1.f,
	//	//	 1.5f,  0.5f, 0.0f,		0.0f, 0.0f, 1.0f, 1.0f,		1.f, 1.f,				1.f,
	//	//	 0.5f,  0.5f, 0.0f,		1.0f, 1.0f, 0.0f, 1.0f,		0.f, 1.f,				1.f
	//	//};

	//	uint32_t indexCount = 0;

	//	std::array<Vertex, 1000> vertices; // vertices to draw??
	//	Vertex* buffer = vertices.data();

	//	for (int y = 0; y < 5; ++y)
	//	{
	//		for (int x = 0; x < 5; ++x)
	//		{
	//			buffer = CreateQuad(buffer, x, y, 1.f);
	//			indexCount += 6;
	//		}
	//	}


	//	//auto q0 = CreateQuad(-1.5f, -0.5f, 0.0f); // first quad
	//	//auto q1 = CreateQuad(0.5f, -0.5f, 0.0f); // second quad

	//	//Vertex vertices[8];
	//	//memcpy(vertices, q0.data(), q0.size() * sizeof(Vertex));
	//	//memcpy(vertices + q0.size(), q1.data(), q1.size() * sizeof(Vertex));


	//	// set dynamic vertex buffer
	//	glBindBuffer(GL_ARRAY_BUFFER, m_quadVB);
	//	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data()); // sends data into the buffer


	//	ResourceHolder<Shader>::GetInstance().GetResource("Batched_Sprite").Activate();

	//	// TODO;
	//	// Bind texture unit 0
	//	// Bind texture unit 1

	//	// get view projection matrix from Camera...
	//		
	//	// shader-> set view projection (pass in the one from camera)
	//	// shader -> set transform



	//	glBindVertexArray(m_quadVAO);
	//	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);


	//	// FINSIEHD!!









	//	


	//	// m_shader->Activate();


	//	// glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

	//	// Have as members?
	//	glm::mat4 model = glm::mat4(1.f);
	//	//glm::mat4 view			= glm::mat4(1.f); 
	//	//glm::mat4 projection	= glm::mat4(1.f);



	//	// TODO; Size...

	//	// model = glm::rotate(model, glm::radians(someData.m_rotation), glm::vec3(1.f, 0.f, 0.f));	// last is rotation angle (pass in data?)
	//	

	//	// TEST
	//	model = glm::scale(model, glm::vec3(1.f, 1.f, 1.f));
	//	//model = glm::translate(model, glm::vec3(someData.m_position.x, someData.m_position.y, someData.m_position.z));


	//	//view = glm::translate(view, glm::vec3(0.f, 0.f, -3.0f));	// Position?
	//	//projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

	//	if (m_camera)
	//	{
	//		const auto& attrib = m_camera->m_attributes;
	//		glm::vec3 position = { attrib.m_position.x,	attrib.m_position.y,	attrib.m_position.z };
	//		glm::vec3 front = { attrib.m_front.x,		attrib.m_front.y,		attrib.m_front.z };
	//		glm::vec3 up = { attrib.m_up.x,			attrib.m_up.y,			attrib.m_up.z };

	//		glm::mat4 view = glm::lookAt(position, position + front, up);
	//		m_shader->SetMatrix4("view", view);
	//	}


	//	m_shader->SetMatrix4("model", model);

	//	// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	//	//m_shader->SetMatrix4("projection", projection); 
	//	m_shader->SetVector4f("Color", someData.m_color);




	//	/* Bind Texutre */
	//	glActiveTexture(GL_TEXTURE0);
	//	someData.m_texture.Bind();

	//	/* Draw */
	//	glBindVertexArray(m_quadVAO);
	//	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	//	glBindVertexArray(0);
	//}

	//void SpriteRenderer::RenderInstanced(const std::vector<CU::Vector3<float>> somePositions)
	//{
	//	// glDrawElementsInstanced(); // also takes an instance count (number of instances we want to render)
	//}

	//Vertex* SpriteRenderer::CreateQuad(Vertex* target, float aX, float aY, float aTextureID)
	//{
	//	float size = 1.f;

	//	// Vertex 1
	//	target->Position	= { aX, aY, 0.f };
	//	target->Color		= { 1.f, 0.f, 0.f, 1.f };
	//	target->TexCoords	= { 0.f, 0.f };
	//	target->TexIndex	 = aTextureID;
	//	++target;

	//	// Vertex 2
	//	target->Position	= { aX + size, aY, 0.f };
	//	target->Color		= { 1.f, 0.f, 0.f, 1.f };
	//	target->TexCoords	= { 1.f, 0.f };
	//	target->TexIndex	= aTextureID;
	//	++target;

	//	// Vertex 3
	//	target->Position	= { aX + size, aY + size, 0.f };
	//	target->Color		= { 1.f, 0.f, 0.f, 1.f };
	//	target->TexCoords	= { 1.f, 1.f };
	//	target->TexIndex	= aTextureID;
	//	++target;

	//	// Vertex 4
	//	target->Position	= { aX, aY + size, 0.f };
	//	target->Color		= { 1.f, 0.f, 0.f, 1.f };
	//	target->TexCoords	= { 0.f, 1.f };
	//	target->TexIndex	= aTextureID;
	//	++target;

	//	return target;
	//}
}