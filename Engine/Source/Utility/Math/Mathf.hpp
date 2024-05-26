#pragma once

//#define PI 3.14159265358979323846

namespace Hi_Engine::Math
{
	constexpr double PI = 3.14159;

	template <typename T>
	T Min(T value1, T value2)
	{
		return value1 < value2 ? value1 : value2;
	}
	
	template <typename T>
	T Max(T value1, T value2)
	{
		return value1 > value2 ? value1 : value2;
	}

	template <typename T>
	T Abs(T value)
	{
		return value < 0 ? -value : value;
	}

	template <typename T>
	T Clamp(T value, T min, T max)
	{
		assert(max >= min);
		return std::max(min, std::min(max, value));
	}

	template <typename T>
	T Lerp(T a, T b, T c)
	{
		T result = (a + c * (b - a));
		return result;
	}

	template <typename T>
	void Swap(T& value1, T& value2)
	{
		T temp = value1;
		value1 = value2;
		value2 = temp;
	}

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
	T ConvertRadiansToDegrees(T radians) // Todo remove??
	{
		return (radians * (180 / PI));
	}

	template <typename T>
	T ConvertDegreesToRadians(T degrees) // Todo remove??
	{
		return (degrees * (PI / 180));
	}

	inline bool IsNearlyEqual(float value1, float value2, float epsilon = 0.0001f) // not checked...
	{
		return std::abs(value1 - value2) < epsilon * std::abs(value1);
	}

	// deleted template specializations
#pragma region Deleted_Template_Specializations

	template <>
	const char* Abs(const char* value) = delete;

	template <>
	std::string Abs(std::string value) = delete;

	template <>
	const char* Clamp(const char* value, const char* min, const char* max) = delete;
	
	template <>
	std::string Clamp(std::string value, std::string min, std::string max) = delete;

	template <>
	const char* Lerp(const char* a, const char* b, const char* c) = delete;

	template <>
	std::string Lerp(std::string a, std::string b, std::string c) = delete;

	template <>
	const char* ConvertToRadians(const char* degrees) = delete;

	template <>
	std::string ConvertToRadians(std::string degrees) = delete;

	template <>
	const char* ConvertToDegrees(const char* radians) = delete;

	template <>
	std::string ConvertToDegrees(std::string radians) = delete;		

#pragma endregion Deleted_Template_Specializations
}