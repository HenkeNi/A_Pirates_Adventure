 #include "Pch.h"
#include "Camera.h"


namespace Hi_Engine
{
	Camera::Camera()
		: m_zoom{ 45.f }, m_windowSize{ 1400, 800 } // TODO; FIX! Listen to event?!
	{
		SetDefaultData();

		//m_data.m_movementSpeed = 1;




		//glm::vec3 direction;
		//direction.y = sin(glm::radians(m_pitch)); // TEST
		//auto normalized = glm::normalize(direction);
		//m_data.m_front = { normalized.x, normalized.y, normalized.z };

	}

	glm::mat4 Camera::GetViewMatrix()
	{
		auto position = m_attributes.m_position;
		return glm::lookAt(m_attributes.m_position, m_attributes.m_position + m_attributes.m_front, m_attributes.m_up);
	}

	glm::mat4 Camera::GetProjectionMatrix()
	{
		// precalculate every time window changes??
		return glm::perspective(glm::radians(GetZoom()), (float)m_windowSize.x / (float)m_windowSize.y, 0.1f, 100.0f);
	}

	void Camera::Init(const CU::Vector3<float> aPosition)
	{
	}

	void Camera::SetPosition(const CU::Vector3<float> aPosition)
	{
		m_attributes.m_position = { aPosition.x, aPosition.y, aPosition.z };
	}

	void Camera::SetDefaultData()
	{
		/* Set default position */
		m_attributes.m_position = { 0.f, 0.f, 3.f };

		m_attributes.m_up = { 0.f, 1.f, 0.f };

		m_attributes.m_front = { 0.f, 0.f, -1.f };

		/* Set default front */
		m_attributes.m_front;
		m_attributes.m_up;

	}

	void Camera::UpdateFrontVector()
	{
		glm::vec3 m_front;
		//front.x
	}

	void Camera::OnWindowResized(const CU::Vector2<unsigned>& aSize)
	{

	}
}