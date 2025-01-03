#pragma once
#include "System.h"

namespace Hi_Engine
{
	class TransformSystem : public System
	{
	public:
		void Update(float deltaTime) override;

	private:
		void UpdateSubEntities();
		void UpdateOrientation();
	};
}