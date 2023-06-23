#pragma once
#include <Utility/Math/Vectors/Vector3.hpp>
#include "../ComponentBase.h"


struct TransformComponent : public ComponentBase
{
	CommonUtilities::Vector3<float> m_currentPos = { 0.f, 0.f, 0.f };
	CommonUtilities::Vector3<float> m_previousPos = { 0.f, 0.f, 0.f };
	CommonUtilities::Vector3<float> m_scale		= { 1.f, 1.f, 1.f };
	float							m_rotation	= 0.f;
};

struct InputComponent : public ComponentBase
{
	std::unordered_map<Hi_Engine::eInputType, bool> m_inputStates; // replace with state instead of bool??
};