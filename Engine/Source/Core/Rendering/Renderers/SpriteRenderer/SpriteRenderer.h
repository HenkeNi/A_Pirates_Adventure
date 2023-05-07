#pragma once

// TODO: Store EBO, VBO as members and delete later? (optional?)
// TODO: Rename 2D renderer?? Also renders billboards?? Also renders planes?? 


namespace Hi_Engine
{
	namespace CU = CommonUtilities;

	class Camera;
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
		void SetCamera(Camera* aCamera);
		void ConfigureShader();

		void Render(const SpriteRenderData& someData);	// Todo; pass in shader as well... maybe camera to..




		void InitBatch();
		void RenderBatch();



		void RenderInstanced(const std::vector<CU::Vector3<float>> somePositions);	// MOVE?? create an InstancedRenderer class??? Struct for InstancedData 

		//void AddRenderCommand();

	private:
		SpriteRenderer();

		Shader*		m_shader;
		unsigned	m_quadVAO;

		// ref to camera?
		Camera*		m_camera; // Or pass in with render data?




		unsigned m_batchQuadVAO;



		// store projection matrix?? => camera updates it??

		// vector<SpriteRenderData>??
	};
}