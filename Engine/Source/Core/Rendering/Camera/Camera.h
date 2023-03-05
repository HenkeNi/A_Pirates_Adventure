#pragma once
#include "Data/Enumerations.h"


namespace Hi_Engine
{
	namespace CU = CommonUtilities;

	class Camera
	{
	public:
		Camera();
		~Camera();

		void Init(const CU::Vector3<float> aPosition);
		//void Update(float aDeltaTime);

		//void SetMovementDirection(eCameraMovement aDirection); // Pass in delta time here??


	private:
		//void CalculateCamera();
		
		CU::Vector2<float> m_position, m_front, m_up;
		// Direction pointing at..
	};

}