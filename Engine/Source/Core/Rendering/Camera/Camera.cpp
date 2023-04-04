 #include "Pch.h"
#include "Camera.h"


namespace Hi_Engine
{
	Camera::Camera()
	{
	}

	void Camera::Init(const CU::Vector3<float> aPosition)
	{
	}

	void Camera::SetPosition(const CU::Vector3<float> aPosition)
	{
		m_data.m_position = aPosition;
	}
}