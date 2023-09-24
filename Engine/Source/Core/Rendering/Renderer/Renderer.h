#pragma once
#include "Data/Structs.h"
#include "Data/Constants.h"
#include "Resources/ResourceHolder.hpp"
#include "Messaging/Listener/EventListener.h"


namespace Hi_Engine
{
	class Window;
	class Camera;

	class Shader;


	// internal messaging system? static..?

	// Possible alternatives; 1) Singleton, 2) Static members, 3) Dependency injection (in Game), 4) Each system have a renderer?...... (currently listens to render commands (events))

	class Renderer : public EventListener
	{
	public:
		Renderer();
		~Renderer();

		void HandleEvent(RenderEvent& anEvent) override;

		void Init();
		void Shutdown();

		void BeginFrame(); 
		void Display();
		void EndFrame();

		void DrawSprite(const SpriteRenderData& someData);
		void DrawQuad(const QuadRenderData& someData);
		
		void SetRenderTarget(Window* aWindow);
		void SetShader(Shader* aShader, bool aSpriteShader = true);

	
		void SetCamera(Camera* aCamera);		// Pass in instead??

		void ProcessCommands();					// ??? ProcessDrawCalls();

	private:
		void CreateQuadBuffers();
		void CreateTextBuffers();
		void DisplayQuads();
		void DisplayText();

		// void SetupVertices(Vertex** aTarget, const glm::vec3& aPosition, const glm::vec2& aSize, const glm::vec4& aColor, float aTexIndex, float aRotation = 0.f);

		


		








		Window*		m_window;
		Camera*		m_camera;			// Pass along the camera instead??


	
		// store a viewport?
			


		// texture manager?
		std::array<uint32_t, 32> m_textureSlots;   // OPEMGL texture id... (or assets have id's)?
		//std::array<uint32_t, Constants::maxTextureSlots> m_textureSlots;   // OPEMGL texture id... (or assets have id's)?
		uint32_t m_textureSlotIndex = 1; // texture 0 == white texture...

		GLuint	 m_whiteTexture = 0;
		uint32_t m_whiteTextureSlot = 0;

		// store render commands?

		RenderContext	m_quadContext;
		RenderContext	m_textContext;
		RenderStats		m_stats; 



		// uint16_t	m_indexCount = 0;
		//Shader*		m_activeShader;
		//Vertex*		m_buffer;
		//Vertex*		m_currentVertex;		// unsigned	m_currentBufferIndex;
		//unsigned	m_VAO, m_VBO, m_EBO;

		//ResourceHolder<Texture2D>		m_textureHolder;
		//ResourceHolder<Shader>		m_shaderHolder;
	};
}