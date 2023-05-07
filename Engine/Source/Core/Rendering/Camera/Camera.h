#pragma once
#include "Data/Enumerations.h"
#include "Data/Structs.h"


namespace Hi_Engine
{
	namespace CU = CommonUtilities;

	// Create orthographic and perspective cameras??

	class Camera // Virtual??
	{
	public:
		Camera();
		
		glm::mat4 GetViewMatrix();
		//virtual ~Camera() = default;	// Remove??

		void Init(const CU::Vector3<float> aPosition);	// Parse from json...? CameraData?
		//void Update(float aDeltaTime);

		//void SetMovementDirection(eCameraMovement aDirection); // Pass in delta time here??

		// get view matrix??


		void SetPosition(const CU::Vector3<float> aPosition);

	private:
		friend class SpriteRenderer; // Or just have getters??

		void SetDefaultData();

		void UpdateFrontVector(); // reanem RecalculateFrontVector??

		//void CalculateCamera();
		
		//glm::vec3 m_position;
		//glm::quat m_orientation;

		// ref to window?

		// store as members instead??
		CameraAttributes	m_attributes;	
		EulerAngles			m_eulerAngles;

		
		
		//CU::Vector3<float> m_position, m_front, m_up;
		// Direction pointing at..



		// FOV
		// aspect?
		// furstrum near and far?

		// perspecitve matrix`?



		
		//float	  m_movementSpeed, m_zoomSpeed;
	};

}