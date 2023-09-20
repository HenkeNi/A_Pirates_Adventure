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

	// TODO; listen to render commands...
	class Renderer : public EventListener
	{
	public:
		Renderer();
		~Renderer();

		void HandleEvent(RenderEvent& anEvent) override;

		void Init(Window* aTarget);
		void Shutdown();

		void Reset();			// Clear? BeginFrame() 
		void Display();

		// void DrawSprite(const SpriteRenderData& someData);
		//void DrawQuad(const PrimitiveRenderData& someData);

		void DrawQuad(const glm::vec3& aPosition, const glm::vec2& aSize, const glm::vec4& aColor);	// Rename; AddRenderCommand()?
		void DrawQuad(const glm::vec3& aPosition, const glm::vec2& aSize, uint32_t aTextureID, float aRotation);

		void SetShader(Shader* aShader);
		void SetCamera(Camera* aCamera);


		//void Render(const SpriteRenderData& someData);
		//void Render(const TextRenderData& someData);
		//void Render(const RectRenderData& someData);
		// void Render(const LineRenderData& someData);

		// 	void LoadResources();

		// static Vertex* CreateQuad(Vertex* aTarget, float x, float y, float aTexIndex);
		//static std::array<Vertex, 4> CreateQuad(float x, float y, float aTexID);

	private:
		friend class RendererProxy;

		// void GenerateIndices(uint32_t* someIndices);
		void SetupVertices(Vertex** aTarget, const glm::vec3& aPosition, const glm::vec2& aSize, const glm::vec4& aColor, float aTexIndex, float aRotation = 0.f);
		bool IsBufferFull() const;

		void ResetStats(); // Or do in BeginFrame?!

		Vertex*		m_buffer;
		Vertex*		m_currentVertex;		// unsigned	m_currentBufferIndex;
		unsigned	m_VAO, m_VBO, m_EBO;


		Window*		m_target;
		Camera*		m_camera;
		Shader*		m_activeShader;


		uint16_t	m_indexCount = 0;
		uint32_t	m_drawCount = 0;

		unsigned m_quadCount = 0; // FIX...

		
		//ResourceHolder<Texture2D>		m_textureHolder;
		//ResourceHolder<Shader>		m_shaderHolder;

	
		// store render commands?

		struct Stats
		{
			uint32_t DrawCount = 0;
			uint16_t QuadCount = 0;
		};

		glm::vec4 quadVertexPositions[4];		// rename defaultQuadPositions?
		glm::vec2 quadTexturePositions[4];	// reanem TextureCoordinates? or TexCoords TextureCoords
		// store a viewport?


		std::array<uint32_t, 32> m_textureSlots;   // OPEMGL texture id... (or assets have id's)?
		//std::array<uint32_t, Constants::maxTextureSlots> m_textureSlots;   // OPEMGL texture id... (or assets have id's)?
		uint32_t m_textureSlotIndex = 1; // texture 0 == white texture...



		GLuint m_whiteTexture = 0;
		uint32_t m_whiteTextureSlot = 0;



		// Render stats
		// DrawCallsPerFrame
		// QuadsDrawn
	};
}