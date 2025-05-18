#pragma once
#include "System.h"

namespace Hi_Engine
{
	class CameraSystem : public System
	{
	public:
		CameraSystem(ECSCore& ecs);

		void Update(float deltaTime) override;
		eUpdatePhase GetUpdatePhase() const override;
	};
}
