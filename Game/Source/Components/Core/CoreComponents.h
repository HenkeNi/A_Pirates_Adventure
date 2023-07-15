#pragma once
#include <Utility/Math/Vectors/Vector3.hpp>
#include "../Base/ComponentBase.h"

namespace CU = CommonUtilities;

struct TransformComponent : public ComponentBase
{
	CU::Vector3<float> m_currentPos = { 0.f, 0.f, 0.f };
	CU::Vector3<float> m_previousPos = { 0.f, 0.f, 0.f };	// add desired position?
	CU::Vector3<float> m_scale		= { 1.f, 1.f, 1.f };
	float							m_rotation	= 0.f;
};

struct InputComponent : public ComponentBase
{
	std::unordered_map<Hi_Engine::eInputType, bool> m_inputStates; // replace with state instead of bool??
};