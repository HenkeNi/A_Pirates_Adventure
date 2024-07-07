#pragma once
#include "../../Modules/Base/Module.h"
#include "../../../Data/Structs.h"
#include "../../../Data/Constants.h"
#include "../../Messaging/Listener/EventListener.h"
#include <queue>
//#include <../../../ThirdParty/GLEW/include/GL/glew.h> //FIX! dont include later...
// #include <Dependencies/GLEW/include/GL/glew.h>
#include "Dependencies/GLEW/include/GL/glew.h"

namespace Hi_Engine
{
	class GLSLShader;

	// 	separe veiw ports for HUD and game
	// internal messaging system? static..?
	// have function for enabling line rendering..?


	// TODO; use glGetError()
	class Renderer : public Module, public EventListener
	{
	public:
		Renderer(int initOrder);
		~Renderer();

		bool Init()				override;
		void Shutdown()			override;
		
		void Deserialize(const rapidjson::Value& json) override;
		void HandleEvent(SpriteBatchRequest& renderEvent) override;

		void ProcessCommands();
		void BeginFrame(); // BeginBatch?
		void EndFrame();
		void Display();

		void DrawSprite(const Sprite& sprite);
		void DrawQuad(const QuadRenderData& data);

		void SetShader(GLSLShader* shader);
		bool IsTextureBound(unsigned texID, float& outTexIndex);

	private:
		void SetupVertexArray();

		std::queue<SpriteBatch> m_spriteBatches;

		// store a viewport?
		
		// Texture manager?
		std::array<uint32_t, Constants::MaxTextureSlots> m_textureSlots;
		uint32_t	m_textureSlotIndex = 1; // texture 0 == white texture...

		// remove?
		GLuint		m_whiteTexture = 0;
		uint32_t	m_whiteTextureSlot = 0;


		RenderContext	m_quadContext;
		RenderContext	m_textContext;
		RenderStats		m_stats;
	};
}