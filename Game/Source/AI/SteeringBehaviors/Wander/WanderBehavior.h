#pragma once
#include "../Base/SteeringBehavior.h"
//#include "Data/Structs.h"
//#include "../../../Data/Structs.h"
#include <Source/Utility/Math/Vectors/Vector.hpp> // NEEDED`?

namespace CU = CommonUtilities;

class WanderBehavior : public SteeringBehavior
{
public:
	WanderBehavior();

	void Update(float deltaTime) override;

	const CU::Vector2<float> GetSteeringForce(const CU::Vector2<float>& velocity) override;


private:
	// TODO; listen to Timer??
	void Wander();

	void Seek();
	void SetNewTarget();
	bool ShouldChangeDir() const;

	void SetAngle(CU::Vector2<float>& velocity, float value);


	Range<float> m_walkDuration;
	//Timer		 m_timer;
	CU::Vector2<float> m_window;

	/* Larger distance to circle means wider movement arcs - will cover more ground before changing direction.. smaller will result in more  tighter turns and more frequent changes in direction */
	const float m_distanceToSteeringCircle; // circleDistance
	const float m_steeringCircleRadius; // circleRadius
	const float m_angleChange;
	float		m_wanderAngle;



	bool m_shouldSeek;
};

