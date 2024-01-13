#pragma once
#include "../../../Data/Structs.h"
#include "../../../Data/Constants.h"
#include "Messaging/Listener/EventListener.h"
#include <queue>

namespace Hi_Engine
{
	class Shader;

	// internal messaging system? static..?
	// Possible alternatives; 1) Singleton, 2) Static members, 3) Dependency injection (in Game), 4) Each system have a renderer?...... (currently listens to render commands (events))
		// have function for enabling line rendering..?

	class Renderer : public EventListener
	{
	public:
		Renderer();
		~Renderer();

		void Init();
		void Shutdown();

		void HandleEvent(RenderEvent& anEvent) override;
		void ProcessCommands();
		void Reset();

		void DrawSprite(const SpriteRenderData& someData);
		void DrawQuad(const QuadRenderData& someData);


		//void SetRenderContext(); // proj matrix, shader... 
		// bool IsContextBound() const; // ????


		// Begin, End  Submit
		void BeginFrame();	// BeginScene Reset
		void Display();		// 
		void EndFrame();


		//void SetRenderState();
		//void SetRenderingContext(); // UI, Sprites, etc...
		// void SetRenderingMode();

		// void SetRenderMode();

		void SetProjectionMatrix(const glm::mat4& aMatrix);
		void SetShader(Shader* aShader);

		bool IsTextureBound(unsigned aTexID, float& outTexIndex);
		// void ProcessCommands();					// ??? ProcessDrawCalls();

	private:
		void DisplayQuads();
		void DisplayText();


		// SceneData m_sceneData;

		// std::queue<RenderCommand> m_renderCommands;
		std::queue<std::queue<RenderCommand>> m_renderSequence;

		// Store render commands?!
		// store a viewport?
		

		// Texture manager?
		std::array<uint32_t, Constants::MaxTextureSlots> m_textureSlots;
		uint32_t	m_textureSlotIndex = 1; // texture 0 == white texture...
		GLuint		m_whiteTexture = 0;
		uint32_t	m_whiteTextureSlot = 0;


		RenderContext	m_quadContext;
		RenderContext	m_textContext;

		RenderStats		m_stats; 
		// store render commands?
	};




	struct SpriteBatch
	{

	};

	struct SceneData
	{
		glm::mat4 ViewProjectionMatrix;
		Shader* Shader;
	};

	class Renderer2D
	{
	public:
		void BeginScene(const glm::mat4& aMatrix);

	private:
	};

}