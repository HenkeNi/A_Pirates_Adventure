#pragma once
#include <Utility/Math/Vectors/Vector3.hpp>
#include "../Base/Component.h"

namespace CU = CommonUtilities;

struct TransformComponent : public Component
{
	Hi_Engine::Transform Transform;

	CU::Vector3<float> CurrentPos = { 0.f, 0.f, 0.f };
	CU::Vector3<float> PreviousPos = { 0.f, 0.f, 0.f };	// add desired position?
	CU::Vector3<float> Scale		= { 1.f, 1.f, 1.f };
	float							Rotation	= 0.f;
};

struct InputComponent : public Component
{
	std::unordered_map<Hi_Engine::eKey, bool> InputStates; // replace with state instead of bool??
	CU::Vector2<double>						  MousePosition;
};

