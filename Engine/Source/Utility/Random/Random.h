#pragma once

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
}