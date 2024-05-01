#pragma once
 #include "../../../Data/Enumerations.h"
#include <../../ThirdParty/glm/glm.hpp>
#include "../../../Utility/Math/Range/Range.hpp"

namespace Hi_Engine
{
	using namespace Math;
	// listen to window changed?! size!
	class Camera
	{
	public:
		Camera();
		Camera(const Rect& rect);
		
		void Init(const Vector2<float>& position);	// Parse from json...? CameraData?
		void SetPosition(const Vector2<float>& position);
		void SetZoomRange(const Range<float>& range);

		void AdjustZoom(float adjustment);
		void ResetZoom();

		glm::mat4 GetViewProjectionMatrix() const;
		glm::mat4 GetProjectionMatrix() const;
		glm::mat4 GetViewMatrix() const;
	
	private:
		void RecalculateMatrixes();
		void OnWindowResized(const Vector2<unsigned>& size);
	
		glm::vec2 m_position; // focus position, center position.?
		Range<float> m_zoomRange;

		float m_aspectRatio;
		float m_rotation;
		float m_zoom;

		// USe dirty flag and matrixes?

		glm::mat4 m_viewProjectionMatrix;
		glm::mat4 m_projectionMatrix;
		glm::mat4 m_viewMatrix;
	};
}