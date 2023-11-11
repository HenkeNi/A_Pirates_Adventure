#pragma once
#include "../../../Data/Structs.h"
#include "../../../Data/Constants.h"
#include "Messaging/Listener/EventListener.h"

// FIX!
//#include <mutex>
#include <queue>

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

		void Init();
		void Shutdown();
		void SwapBuffers();

		void HandleEvent(RenderEvent& anEvent) override;
		bool IsTextureBound(unsigned aTexID, float& outTexIndex);
		void ProcessCommands();

		void DrawSprite(const SpriteRenderData& someData);
		void DrawQuad(const QuadRenderData& someData);

		void BeginFrame(); 
		void Display();
		void EndFrame();

		void SetRenderTarget(Window* aWindow);
		void SetShader(Shader* aShader);
		void SetCamera(Camera* aCamera);		// Pass in instead??

		bool IsReady() { return !m_backBuffer.empty(); }

		inline const RenderStats& GetRenderStats() const { return m_stats; }

	private:
		//void DisplayQuads();
		//void DisplayText();

		Window*		m_window;
		Camera*		m_camera;			// Pass along the camera instead?? or maybbe no need to store? instead set the uProjectioView in shader when needed? 

		// store a viewport?


		std::queue<RenderCommand> m_renderCommands; // Replace with RenderCommand -- is it fine that set camera -> set shader, etc is stored here as well?

		std::queue<RenderCommand> m_frontBuffer; // Array instead?? dont pop?!
		std::queue<RenderCommand> m_backBuffer;
	
		//std::mutex m_queueMutex;


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
}