#pragma once


// Rename 2D renderer?? Also renders billboards??

	// Also renders planes?? 

namespace Hi_Engine
{
	class Shader;
	struct SpriteRenderData;

	class SpriteRenderer
	{
	public:
		~SpriteRenderer();
		SpriteRenderer(const SpriteRenderer&)				= delete;
		SpriteRenderer& operator=(const SpriteRenderer&)	= delete;

		static SpriteRenderer& GetInstance();

		void Init();
		//void SetAndConfigureShader();
		void SetShader(Shader* aShader);
		void ConfigureShader(float aWidth, float aHeight); // Private

		void Render(const SpriteRenderData& someData);

		//void AddRenderCommand();

	private:
		SpriteRenderer();
		
		Shader*		m_shader;
		unsigned	m_quadVAO;

		// vector<SpriteRenderData>??
	};
}