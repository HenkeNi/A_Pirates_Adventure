#pragma once
#include "../../Modules/Base/Module.h"
#include "../../../Data/Structs.h"
#include "../../../Data/Constants.h"
#include "../../Messaging/Listener/EventListener.h"
#include <queue>
#include <../../../ThirdParty/GLEW/include/GL/glew.h> //FIX! dont include later...

namespace Hi_Engine
{
	class GLSLShader;

// 	separe veiw ports for HUD and game

	// internal messaging system? static..?
	// Possible alternatives; 1) Singleton, 2) Static members, 3) Dependency injection (in Game), 4) Each system have a renderer?...... (currently listens to render commands (events))
		// have function for enabling line rendering..?

	//class EventListener;

	class Renderer : public Module, public EventListener
	{
	public:
		Renderer(int initOrder);
		~Renderer();

		bool Init()				override;
		void Shutdown()			override;
		void Deserialize(const rapidjson::Value& json) override;

		void HandleEvent(RenderEvent& renderEvent) override;
		void ProcessCommands();
		void Reset();

		void DrawSprite(const SpriteRenderData& data); // RenderData RenderInfo RenderSPecs RenderCOnfigs
		void DrawQuad(const QuadRenderData& data);

		// TODO; use glGetError()

		//void SetRenderContext(); // proj matrix, shader... 
		// bool IsContextBound() const; // ????


		// Begin, End  Submit
		void BeginFrame();	// BeginScene Reset // 
		void Display();		// 
		void EndFrame();

		// BeginSpriteBatch(Camera, GLSLShader);

		//void SetRenderState();
		//void SetRenderingContext(); // UI, Sprites, etc...
		// void SetRenderingMode();

		// void SetRenderMode();

		void SetProjectionMatrix(const glm::mat4& matrix);
		void SetShader(GLSLShader* shader);

		bool IsTextureBound(unsigned texID, float& outTexIndex);
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
		GLSLShader* GLSLShader;
	};

	class Renderer2D
	{
	public:
		void BeginScene(const glm::mat4& matrix);

	private:
	};

}