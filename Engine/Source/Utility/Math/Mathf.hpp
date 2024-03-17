#pragma once
#include "Vectors/Vector.hpp"
#include "../glm/glm.hpp"

#define PI 3.14159265358979323846

namespace CommonUtilities
{
	template <typename T>
	inline T ConvertToRadians(T degrees)
	{
		return degrees * (PI / 180);
	}

	template <typename T>
	inline T ConvertToDegrees(T radians)
	{
		return 180 * (radians / PI);
	}

	template <typename T>
	inline glm::vec2 ConvertVecToGlm(const Vector2<T>& vector)
	{
		return glm::vec2{ vector.x, vector.y };
	}

	template <typename T>
	inline glm::vec3 ConvertVecToGlm(const Vector3<T>& vector)
	{
		return glm::vec3{ vector.x, vector.y, vector.z };
	}

	inline bool IsNearlyEqual(float value1, float value2, float epsilon = 0.0001f) // not checked...
	{
		return std::abs(value1 - value2) < epsilon * std::abs(value1);
	}
}