#pragma once
//#include "../Core/Modules/Module.h"
#include "../RenderTypes.h"
#include <queue>
#include "../Services/IService.h"
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


	class IRenderer : public IService
	{

	};

	// TODO; use glGetError()
	class Renderer : public IRenderer
	{
	public:
		Renderer(Window& window);
		~Renderer();

		bool Initialize()		override;
		void Shutdown()			override;
		
		//void Deserialize(const rapidjson::Value& json) override;
		void Deserialize(const rapidjson::Value& json);
		void SetProjectionMatrix(const glm::mat4& proj);
		void AddSpriteBatch(SpriteBatch&& batch); // or just render sprite batch? Make tempalted?

		void BeginFrame();
		void ProcessBatches();
		void EndFrame();


		// PRIVATE?
		void Display();

		void DrawSprite(const Sprite& sprite);
		void DrawQuad(const QuadRenderData& data);
		// PRIVATE?

		void SetShader(GLSLShader* shader);
		bool IsTextureBound(unsigned texID, float& outTexIndex);

		void ClearScreen(); // Remove later? rework into BeginFrame() or something...

	private:
		void SetupVertexArray();
		void BeginNewBatch(); // or ResetContext?

		std::queue<SpriteBatch> m_spriteBatches; // render commands? pool??

		// store a viewport?


		// Texture manager?
		std::array<uint32_t, MaxTextureSlots> m_textureSlots;
		uint32_t	m_textureSlotIndex = 1; // texture 0 == white texture...

		// remove?
		GLuint		m_whiteTexture = 0;
		uint32_t	m_whiteTextureSlot = 0;

		RenderContext	m_quadContext;
		RenderStats		m_stats;
		Window& m_window; // dont? instead fetch from modulemanager?
	};
}