#pragma once
#include "Vectors/Vector.hpp"
#include "../glm/glm.hpp"

#define PI 3.14159265358979323846

namespace CommonUtilities
{
	template <typename T>
	inline T ConvertToRadians(T aDegrees)
	{
		return aDegrees * (PI / 180);
	}

	template <typename T>
	inline T ConvertToDegrees(T aRadians)
	{
		return 180 * (aRadians / PI);
	}

	template <typename T>
	inline glm::vec2 ConvertVecToGlm(const Vector2<T>& aVector)
	{
		return glm::vec2{ aVector.x, aVector.y };
	}

	template <typename T>
	inline glm::vec3 ConvertVecToGlm(const Vector3<T>& aVector)
	{
		return glm::vec3{ aVector.x, aVector.y, aVector.z };
	}

	inline bool IsNearlyEqual(float aFirst, float aSecond, float anEpsilon = 0.0001f) // not checked...
	{
		return std::abs(aFirst - aSecond) < anEpsilon * std::abs(aFirst);
	}
}