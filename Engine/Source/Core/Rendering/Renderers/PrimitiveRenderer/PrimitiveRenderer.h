#pragma once

namespace Hi_Engine
{
	namespace CU = CommonUtilities;

	class Camera;
	struct PrimitiveRenderData;

	class PrimitiveRenderer
	{
	public:
		~PrimitiveRenderer();
		PrimitiveRenderer(const PrimitiveRenderer&)				= delete;
		PrimitiveRenderer& operator=(const PrimitiveRenderer&)	= delete;

		static PrimitiveRenderer& GetInstance();

		void Init();
		void Shutdown();

		void Render(const PrimitiveRenderData& someData);
		void SetCamera(Camera* aCamera);
	
	private:
		PrimitiveRenderer();

		Camera*					m_camera;
		CU::Vector2<unsigned>	m_windowSize;	// FIX LATER...
		unsigned				m_VAO;
	};
}