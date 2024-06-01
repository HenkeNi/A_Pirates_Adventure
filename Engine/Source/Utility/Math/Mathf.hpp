#pragma once

//#define PI 3.14159265358979323846

namespace Hi_Engine::Math
{
	constexpr double PI = 3.14159;

	// ################## Min ################## //
	template <typename T>
	constexpr T Min(T value1, T value2)
	{
		return value1 < value2 ? value1 : value2;
	}
	
	// ################## Max ################## //
	template <typename T>
	constexpr T Max(T value1, T value2)
	{
		return value1 > value2 ? value1 : value2;
	}

	// ################## Abs ################## //
	template <typename T>
	constexpr T Abs(T value)
	{
		return value < 0 ? -value : value;
	}

	template <>
	const char* Abs(const char* value) = delete;
	
	template <>
	std::string Abs(std::string value) = delete;


	// ################## Clamp ################## //
	template <typename T>
	constexpr T Clamp(T value, T min, T max)
	{
		assert(max >= min);
		return std::max(min, std::min(max, value));
	}

	template <>
	const char* Clamp(const char* value, const char* min, const char* max) = delete;

	template <>
	std::string Clamp(std::string value, std::string min, std::string max) = delete;

	// ################## Lerp ################## //
	template <typename T>
	constexpr T Lerp(T a, T b, T c)
	{
		T result = (a + c * (b - a));
		return result;
	}

	template <>
	const char* Lerp(const char* a, const char* b, const char* c) = delete;

	template <>
	std::string Lerp(std::string a, std::string b, std::string c) = delete;

	// ################## Swap ################## //
	template <typename T>
	void Swap(T& value1, T& value2)
	{
		T temp = value1;
		value1 = value2;
		value2 = temp;
	}

	// ################## Convert to radians ################## //
	template <typename T>
	constexpr T ConvertToRadians(T degrees)
	{
		return degrees * (PI / 180);
	}

	template <>
	const char* ConvertToRadians(const char* degrees) = delete;

	template <>
	std::string ConvertToRadians(std::string degrees) = delete;

	// ################## Convert to degrees ################## //
	template <typename T>
	constexpr T ConvertToDegrees(T radians)
	{
		return 180 * (radians / PI);
	}

	template <>
	const char* ConvertToDegrees(const char* radians) = delete;

	template <>
	std::string ConvertToDegrees(std::string radians) = delete;

	template <typename T>
	constexpr T ConvertRadiansToDegrees(T radians) // Todo remove??
	{
		return (radians * (180 / PI));
	}

	template <typename T>
	constexpr T ConvertDegreesToRadians(T degrees) // Todo remove??
	{
		return (degrees * (PI / 180));
	}

	inline bool IsNearlyEqual(float value1, float value2, float epsilon = 0.0001f) // not checked...
	{
		return std::abs(value1 - value2) < epsilon * std::abs(value1);
	}
}