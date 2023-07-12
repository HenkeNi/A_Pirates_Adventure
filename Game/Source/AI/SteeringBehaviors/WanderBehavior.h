#pragma once
#include "SteeringBehavior.h"
//#include "Data/Structs.h"
#include "../../Data/Structs.h"

class WanderBehavior : public SteeringBehavior
{
public:
	WanderBehavior();

	void Update(float aDeltaTime) override;

	const CU::Vector3<float> GetSteeringForce(const CU::Vector3<float>& aVelocity) override;


private:
	// TODO; listen to Timer??
	void Wander();

	void Seek();
	void SetNewTarget();
	bool ShouldChangeDir() const;

	void SetAngle(CU::Vector3<float>& aVelocity, float aValue);


	Range<float> m_walkDuration;
	//Timer		 m_timer;
	CU::Vector3<float> m_target;

	/* Larger distance to circle means wider movement arcs - will cover more ground before changing direction.. smaller will result in more  tighter turns and more frequent changes in direction */
	const float m_distanceToSteeringCircle; // circleDistance
	const float m_steeringCircleRadius; // circleRadius
	const float m_angleChange;
	float		m_wanderAngle;



	bool m_shouldSeek;
};

