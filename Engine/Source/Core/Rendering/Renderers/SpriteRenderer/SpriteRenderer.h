#pragma once

namespace Hi_Engine
{
	namespace CU = CommonUtilities;

	class Camera;
	struct SpriteRenderData;

	class SpriteRenderer
	{
	public:
		~SpriteRenderer();
		SpriteRenderer(const SpriteRenderer&)				= delete;
		SpriteRenderer& operator=(const SpriteRenderer&)	= delete;

		static SpriteRenderer& GetInstance();

		void Init();
		void Shutdown();

		void Render(const SpriteRenderData& someData);
		void SetCamera(Camera* aCamera);

	private:
		SpriteRenderer();

		Camera*					m_camera;
		CU::Vector2<unsigned>	m_windowSize;	// FIX LATER...
		unsigned				m_VAO;
	};
}