#pragma once
#include "../Base/SteeringBehavior.h"
//#include "../../../Data/Structs.h"
#include <Source/Utility/Math/Vectors/Vector.hpp> // NEEDED`?

namespace CU = CommonUtilities;

class WanderSeekBehavior : public SteeringBehavior
{
public:
	WanderSeekBehavior();

	void Update(float deltaTime) override;
	const CU::Vector2<float> GetSteeringForce(const CU::Vector2<float>& velocity) override;
	const CU::Vector2<float> GetSteeringForce(const CU::Vector2<float>& position, const CU::Vector2<float>& velocity) override;


private:
	void SetRandomizedTarget();
	bool ShouldChangeDir() const;

	Range<float>		m_walkDurationRange;
	// Timer				m_timer;
	CU::Vector2<float>	m_window;
};