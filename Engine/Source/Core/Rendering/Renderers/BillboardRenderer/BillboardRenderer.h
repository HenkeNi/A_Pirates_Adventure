#pragma once

namespace Hi_Engine
{
	namespace CU = CommonUtilities;

	class Camera;
	struct BillboardRenderData;

	class BillboardRenderer
	{
	public:
		~BillboardRenderer();
		BillboardRenderer(const BillboardRenderer&)				= delete;
		BillboardRenderer& operator=(const BillboardRenderer&)	= delete;

		static BillboardRenderer& GetInstance();

		void Init();
		void Shutdown();

		void Render(const BillboardRenderData& someData);
		void SetCamera(Camera* aCamera);


	private:
		BillboardRenderer();
	
		Camera*					m_camera;
		CU::Vector2<unsigned>	m_windowSize;	// FIX LATER...
		unsigned				m_VAO;
	};
}