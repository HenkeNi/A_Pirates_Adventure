#pragma once
#include "Data/Enumerations.h"
#include "Data/Structs.h"


namespace Hi_Engine
{
	namespace CU = CommonUtilities;

	class Camera // Virtual??
	{
	public:
		Camera();
		virtual ~Camera() = default;

		void Init(const CU::Vector3<float> aPosition);	// Parse from json...? CameraData?
		//void Update(float aDeltaTime);

		//void SetMovementDirection(eCameraMovement aDirection); // Pass in delta time here??

		// get view matrix??

		void SetPosition(const CU::Vector3<float> aPosition);

	private:
		friend class SpriteRenderer; // Or just have getters??

		//void CalculateCamera();
		

		// ref to window?

		CameraData m_data;	// store as members??

		//CU::Vector3<float> m_position, m_front, m_up;
		// Direction pointing at..



		// FOV
		// aspect?
		// furstrum near and far?

		// perspecitve matrix`?
	};

}