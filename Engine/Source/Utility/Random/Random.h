#pragma once
#include "../../Data/Constants.h"

namespace Random
{
	template <typename T>
	T GenerateRandomInteger(T min, T max)
	{
		//static_assert(std::is_integral_v<T> && "T must be an integer type");

		static std::random_device rd;
		static std::mt19937 gen(rd());

		std::uniform_int_distribution<T> dis(min, max);
		return dis(gen);
	}


	template <typename T>
	T GenerateRandomFloatingPoint(T min, T max)
	{
		//static_assert(std::is_floating_point<T> && "T must be a floating-point type")

		static std::random_device rd;
		static std::mt19937 gen(rd());

		std::uniform_real_distribution<T> dis(min, max);
		return dis(gen);
	}

	template <typename T>
	CU::Vector2<T> GenerateRandomFloatingPointInRadius(const CU::Vector2<T>& center, T radius)
	{
		T angle = GenerateRandomFloatingPoint<T>(0.0, 2.0 * 3.14159);
		T randomRadius = GenerateRandomFloatingPoint<T>(0.0, radius);

		T x = center.x + randomRadius * cos(angle);
		T y = center.y + randomRadius * sin(angle);

		return CU::Vector2<T>{ x, y };
	}
}