#pragma once
#include "../Core/Modules/Module.h"
#include "../RenderTypes.h"
#include <queue>
//#include <../../../ThirdParty/GLEW/include/GL/glew.h> //FIX! dont include later...
// #include <Dependencies/GLEW/include/GL/glew.h>
#include "Dependencies/GLEW/include/GL/glew.h"


namespace Hi_Engine
{
	class GLSLShader;
	class Window;
	// 	separe veiw ports for HUD and game
	// internal messaging system? static..?
	// have function for enabling line rendering..?
	constexpr uint32_t MaxTextureSlots = 32;		// Or max textures?


	// TODO; use glGetError()
	class Renderer : public Module
	{
	public:
		Renderer(ModuleManager& manager, Window& window);
		~Renderer();

		bool Init()				override;
		void Shutdown()			override;
		
		void Deserialize(const rapidjson::Value& json) override;

		void BeginDraw();
		void EndDraw();

		void ProcessCommands();
		void BeginFrame(); // BeginBatch?
		void EndFrame();
		void Display();

		void DrawSprite(const Sprite& sprite);
		void DrawQuad(const QuadRenderData& data);

		void SetShader(GLSLShader* shader);
		bool IsTextureBound(unsigned texID, float& outTexIndex);

		void ClearScreen(); // Remove later? rework into BeginFrame() or something...

		void SetProjectionMatrix(const glm::mat4& proj);
		void AddSpriteBatch(SpriteBatch&& batch);

	private:
		void SetupVertexArray();

		std::queue<SpriteBatch> m_spriteBatches;

		// store a viewport?
		
		// Texture manager?
		std::array<uint32_t, MaxTextureSlots> m_textureSlots;
		uint32_t	m_textureSlotIndex = 1; // texture 0 == white texture...

		// remove?
		GLuint		m_whiteTexture = 0;
		uint32_t	m_whiteTextureSlot = 0;

		Window& m_window; // dont? instead fetch from modulemanager?

		RenderContext	m_quadContext;
		//RenderContext	m_textContext;
		RenderStats		m_stats;
	};
}