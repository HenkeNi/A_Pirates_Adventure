#pragma once
#include <../../ThirdParty/glm/glm.hpp>
#include "../../Core/Math/Range/Range.hpp" // try re,pve

namespace Hi_Engine
{
		// Remove later? or using for vec4 together with color?
	struct Rect
	{
		float Top;
		float Bottom;
		float Left;
		float Right;
	};

	//using namespace Math;
	// listen to window changed?! size!
	class Camera
	{
	public:
		Camera();
		Camera(const Rect& rect);
		
		void Init(const FVector2& position);	// Parse from json...? CameraData?
		void SetOrthoProjection(const Rect& rect);
		void SetPosition(const FVector2& position);
		void SetZoomRange(const Math::Range<float>& range);

		void AdjustZoom(float adjustment);
		void ResetZoom();

		glm::mat4 GetViewProjectionMatrix() const;
		glm::mat4 GetProjectionMatrix() const;
		glm::mat4 GetViewMatrix() const;
	
	private:
		void RecalculateMatrixes();
		void OnWindowResized(const UVector2& size);
	
		glm::vec2 m_position; // focus position, center position.?
		Math::Range<float> m_zoomRange;

		float m_aspectRatio;
		float m_rotation;
		float m_zoom;

		// USe dirty flag and matrixes?

		glm::mat4 m_viewProjectionMatrix;
		glm::mat4 m_projectionMatrix;
		glm::mat4 m_viewMatrix;
	};
}