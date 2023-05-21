#include "Pch.h"
#include "OrthographicCamera.h"


#include "gtc/matrix_transform.hpp"


namespace Hi_Engine
{
	OrthographicCamera::OrthographicCamera(const Rect& aRect)
		: m_position{ 0.f, 0.f, 0.f }, m_rotation{ 0.f }
	{
		m_matrices.Projection = glm::ortho(aRect.Left, aRect.Right, aRect.Bottom, aRect.Top, -1.f, 1.f);
		m_matrices.ProjectionView = m_matrices.Projection * m_matrices.View;
	}

	void OrthographicCamera::SetPosition(const glm::vec3& aPosition)
	{
		m_position = aPosition;
		CalculateViewMatrix();
	}

	void OrthographicCamera::SetRotation(float aRotation)
	{
		m_rotation = aRotation;
		CalculateViewMatrix();
	}

	const CameraMatrices& OrthographicCamera::GetMatrices() const
	{
		return m_matrices;
	}


	const glm::vec3& OrthographicCamera::GetPosition() const
	{
		return m_position;
	}

	float OrthographicCamera::GetRotation() const
	{
		return m_rotation;
	}

	void OrthographicCamera::CalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.f), m_position);
		transform = glm::rotate(transform, glm::radians(m_rotation), glm::vec3(0.f, 0.f, 1.f));
		
		m_matrices.View = glm::inverse(transform);
		m_matrices.ProjectionView = m_matrices.Projection * m_matrices.View;
	}
}