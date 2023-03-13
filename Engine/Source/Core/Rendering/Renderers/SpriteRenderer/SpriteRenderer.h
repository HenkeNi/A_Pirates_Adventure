#pragma once

// TODO: Store EBO, VBO as members and delete later? (optional?)
// TODO: Rename 2D renderer?? Also renders billboards?? Also renders planes?? 


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
		void SetShader(Shader* aShader);
		void ConfigureShader();

		void Render(const SpriteRenderData& someData);

		//void AddRenderCommand();

	private:
		SpriteRenderer();

		Shader*		m_shader;
		unsigned	m_quadVAO;

		// vector<SpriteRenderData>??
	};
}