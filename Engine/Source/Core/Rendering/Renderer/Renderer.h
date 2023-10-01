#pragma once
#include "../../../Data/Structs.h"
#include "../../../Data/Constants.h"
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

		void Init();
		void Shutdown();

		void HandleEvent(RenderEvent& anEvent) override;
		bool IsTextureBound(unsigned aTexID, float& outTexIndex);

		void DrawSprite(const SpriteRenderData& someData);
		void DrawQuad(const QuadRenderData& someData);

		void BeginFrame(); 
		void Display();
		void EndFrame();

		void SetRenderTarget(Window* aWindow);
		void SetShader(Shader* aShader, bool aSpriteShader = true);
		void SetCamera(Camera* aCamera);		// Pass in instead??

		void ProcessCommands();					// ??? ProcessDrawCalls();

	private:
		void DisplayQuads();
		void DisplayText();

		Window*		m_window;
		Camera*		m_camera;			// Pass along the camera instead??

		// store a viewport?

		// Texture manager?
		std::array<uint32_t, Constants::maxTextureSlots> m_textureSlots;
		uint32_t	m_textureSlotIndex = 1; // texture 0 == white texture...
		GLuint		m_whiteTexture = 0;
		uint32_t	m_whiteTextureSlot = 0;


		RenderContext	m_quadContext;
		RenderContext	m_textContext;
		RenderStats		m_stats; 

		// store render commands?
	};
}