#pragma once
#include "Camera.h"
//#include <glm/glm.hpp> // Pch not working??
#include <../glm/glm.hpp>

namespace Hi_Engine
{
	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera(const Rect& aRect);

		void					SetPosition(const glm::vec3& aPosition);
		void					SetRotation(float aRotation);

		const CameraMatrices&	GetMatrices() const;
		const glm::vec3&		GetPosition() const;
		float					GetRotation() const;

	private:
		void					CalculateViewMatrix();

		CameraMatrices			m_matrices;
		glm::vec3				m_position;
		float					m_rotation;
	};
}