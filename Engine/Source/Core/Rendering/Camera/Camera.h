#pragma once
#include "../../../Data/Structs.h"
 #include "../../../Data/Enumerations.h"
#include <../../ThirdParty/glm/glm.hpp>

namespace Hi_Engine
{
	namespace CU = CommonUtilities;

	// listen to window changed?! size!
	class Camera
	{
	public:
		Camera();
		Camera(const Rect& rect);
		
		void Init(const CU::Vector3<float> position);	// Parse from json...? CameraData?
		void SetPosition(const CU::Vector3<float>& position);
		void SetZoomRange(const CU::Vector2<float>& range);

		void AdjustZoom(float adjustment);
		void ResetZoom();

		glm::mat4 GetViewProjectionMatrix() const;
		glm::mat4 GetProjectionMatrix() const;
		glm::mat4 GetViewMatrix() const;
	
	private:
		void RecalculateMatrixes();
		void OnWindowResized(const CU::Vector2<unsigned>& size);
	
		glm::vec2 m_position; // focus position, center position.?
		CU::Vector2<float> m_zoomRange;

		float m_aspectRatio;
		float m_rotation;
		float m_zoom;

		// USe dirty flag and matrixes?

		glm::mat4 m_viewProjectionMatrix;
		glm::mat4 m_projectionMatrix;
		glm::mat4 m_viewMatrix;
	};
}