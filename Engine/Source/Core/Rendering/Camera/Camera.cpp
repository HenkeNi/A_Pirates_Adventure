 #include "Pch.h"
#include "Camera.h"
#include "../Utility/Utility/UtilityFunctions.hpp"


namespace Hi_Engine
{

	//void Camera::Init(float left, float right, float bottom, float top, float near, float far)
	//{
	//	m_projectionMatrix = glm::ortho(left, right, bottom, top, near, far);
	//}

	//void Camera::SetPosition(const CU::Vector3<float>& aPosition)
	//{
	//	m_viewMatrix = glm::translate(glm::mat4(1.f), { -aPosition.x, -aPosition.y, -aPosition.z });
	//}


	Camera::Camera()
		:m_aspectRatio{ 1400.f / 800.f }, m_position{ 0.f, 0.f }, m_zoom{ 2.5f }, m_rotation{ 0.f }  // TODO; FIX! Listen to event?!
	{	
	}

	Camera::Camera(const Rect& aRect)
	{
	}

	glm::mat4 Camera::GetViewProjectionMatrix() const
	{
		return GetProjectionMatrix() * GetViewMatrix();
	}

	glm::mat4 Camera::GetProjectionMatrix() const
	{
		float left = -m_zoom * m_aspectRatio;
		float right = m_zoom * m_aspectRatio;
		float bottom = -m_zoom;
		float top = m_zoom;

		return glm::ortho(left, right, bottom, top, -1.f, 100.f);
	}

	glm::mat4 Camera::GetViewMatrix() const
	{
		auto transform = glm::translate(glm::mat4(1.f), { m_position.x, m_position.y, 0.f });
		transform = glm::rotate(transform, m_rotation, glm::vec3(0, 0, 1));

		return glm::inverse(transform);
	}

	void Camera::Init(const CU::Vector3<float> aPosition)
	{
	}

	void Camera::SetPosition(const CU::Vector3<float>& aPosition)
	{
		m_position = { aPosition.x, aPosition.y };
	}

	void Camera::SetZoomRange(const CU::Vector2<float>& aRange)
	{
		m_zoomRange = aRange;
	}

	void Camera::AdjustZoom(float anAdjustment)
	{
		m_zoom = CommonUtilities::Clamp(m_zoom - anAdjustment, m_zoomRange.x, m_zoomRange.y);
	}

	void Camera::ResetZoom()
	{
		m_zoom = 2.5f;
	}

	void Camera::OnWindowResized(const CU::Vector2<unsigned>& aSize)
	{

	}
}