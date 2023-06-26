#pragma once
//#include "../Data/Enumerations.h"
//#include "../Data/Structs.h"
#include "Data/Structs.h"
#include "Data/Enumerations.h"

#include <../../ThirdParty/glm/glm.hpp>
//#include <glm.hpp>

namespace Hi_Engine
{
	namespace CU = CommonUtilities;

	//class Camera
	//{
	//public:
	//	virtual ~Camera() = default;

	//	virtual glm::mat4 GetProjectionMatrix() = 0;
	//	virtual glm::mat4 GetViewMatrix()		= 0;

	//private:
	//	glm::vec3 m_position;
	//	glm::vec3 m_rotation;
	//};




	// listen to window changed?! size!

	class Camera
	{
	public:
		Camera();
		// TOOD; get virtual destructor...
		
		glm::mat4 GetViewMatrix();
		//virtual ~Camera() = default;	// Remove??

		void Init(const CU::Vector3<float> aPosition);	// Parse from json...? CameraData?
		//void Update(float aDeltaTime);

		//void SetMovementDirection(eCameraMovement aDirection); // Pass in delta time here??

		// get view matrix??

		float GetZoom() const
		{
			return m_zoom;
		}

		void SetPosition(const CU::Vector3<float> aPosition);

	private:
		friend class SpriteRenderer; // Or just have getters??

		void SetDefaultData();

		void UpdateFrontVector(); // reanem RecalculateFrontVector??

		//void CalculateCamera();
		
		//glm::quat m_orientation;

		// ref to window?

		// store as members instead??
		CameraAttributes	m_attributes;	
		EulerAngles			m_eulerAngles;

		// Contains a porjection matrix and a view matrix...
		glm::mat4 m_viewMatrix;	// multiply with inverted view matrix...

		// projection matrix? glm::perspective?
		CU::Vector2<unsigned>	m_aspectRatio;
		float					m_FOV; // 45-60

		float m_zoom;


		// FOV
		// aspect?
		// furstrum near and far?

		// perspecitve matrix`?



		
		//float	  m_movementSpeed, m_zoomSpeed;
	};


}