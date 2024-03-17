 #include "Pch.h"
#include "Camera.h"
#include "../Utility/Utility/UtilityFunctions.hpp"


namespace Hi_Engine
{
	Camera::Camera()
		:m_aspectRatio{ 1400.f / 800.f }, m_position{ 0.f, 0.f }, m_zoom{ 1.f }, m_rotation{ 0.f }  // TODO; FIX! Listen to event?!
	{
		float zoom = 2.5f;

		float left = -zoom * m_aspectRatio;
		float right = zoom * m_aspectRatio;
		float bottom = -zoom;
		float top = zoom;

		m_projectionMatrix = glm::ortho(left, right, bottom, top, -1.f, 100.f);
		m_viewMatrix = glm::mat4(1.f);

		m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
	}

	Camera::Camera(const Rect& rect)
	{
	}

	glm::mat4 Camera::GetViewProjectionMatrix() const
	{
		return m_viewProjectionMatrix;
	}

	glm::mat4 Camera::GetProjectionMatrix() const
	{
		return m_projectionMatrix;
	}

	glm::mat4 Camera::GetViewMatrix() const
	{
		return m_viewMatrix;
	}

	void Camera::Init(const CU::Vector3<float> position)
	{
	}

	void Camera::SetPosition(const CU::Vector3<float>& position)
	{
		m_position = { position.x, position.y };
		RecalculateMatrixes();
		
		//m_viewMatrix = glm::translate(glm::mat4(1.f), { -aPosition.x, -aPosition.y, 0.f });
	}

	void Camera::SetZoomRange(const CU::Vector2<float>& range)
	{
		m_zoomRange = range;
	}

	void Camera::AdjustZoom(float adjustment)
	{
		m_zoom = CommonUtilities::Clamp(m_zoom - adjustment, m_zoomRange.x, m_zoomRange.y);
		RecalculateMatrixes();
	}

	void Camera::ResetZoom()
	{
		m_zoom = 1.f;
	}

	void Camera::OnWindowResized(const CU::Vector2<unsigned>& size)
	{

	}

	void Camera::RecalculateMatrixes()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), { m_position.x, m_position.y, 0.f });
		transform = glm::scale(transform, glm::vec3(m_zoom, m_zoom, 1.0f));
		transform = glm::rotate(transform, glm::radians(m_rotation), glm::vec3(0, 0, 1));

		m_viewMatrix = glm::inverse(transform);

		m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
	}
}