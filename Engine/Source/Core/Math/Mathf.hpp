#pragma once

//#define PI 3.14159265358979323846

namespace Hi_Engine::Math
{
	constexpr double PI = 3.14159;

	// ################## Min ################## //
	template <typename T>
	constexpr T Min(T a, T b)
	{
		return a < b ? a : b;
	}
	
	// ################## Max ################## //
	template <typename T>
	constexpr T Max(T a, T b)
	{
		return b < a ? a : b;
	}

	// ################## Abs ################## //
	template <std::totally_ordered T> // check
	constexpr T Abs(T value)
	{
		return value < 0 ? -value : value;
	}

	// ################## Clamp ################## //
	template <std::totally_ordered T> // or integer?
	constexpr T Clamp(T value, T min, T max)
	{
		assert(max >= min);
		return std::max(min, std::min(max, value));
	}

	// ################## Lerp ################## //
	template <std::totally_ordered T> // Check
	constexpr T Lerp(T a, T b, T c)
	{
		T result = (a + c * (b - a));
		return result;
	}

	// ################## Swap ################## //
	template <typename T>
	void Swap(T& a, T& b) // check
	{
		T temp = a;
		a = b;
		b = temp;
	}

	// ################## Swap ################## //
	template <std::integral T>
	T Wrap(T value, T min, T max)
	{
		return (value < min) ? max - (min - value) % (max - min)
			: min + (value - min) % (max - min);
	}

	// ################## Rerange ################## //

	// template <std::ranges::input_range R>
	template <typename T>
	T Rerange(T value, const Range<T>& oldRange, const Range<T>& newRange) // Todo; rename MapToNewRange?
	{
		T newValue = newRange.Min + ((value - oldRange.Min) / (oldRange.Max - oldRange.Min)) * (newRange.Max - newRange.Min);
		return newValue;
	}

	// ################## Angle Conversion Functions ################## //
	template <std::floating_point T>
	constexpr T RadiansToDegrees(T radians)
	{
		return (radians * (T(180) / T(PI)));
	}

	template <std::floating_point T>
	constexpr T DegreesToRadians(T degrees)
	{
		return (degrees * (T(PI) / T(180)));
	}

	// ################## Floating Comparison Functions ################## //
	template <std::floating_point T>
	bool IsNearlyEqual(T a, T b, T epsilon = static_cast<T>(0.0001))
	{
		return std::fabs(a - b) < epsilon;
	}






	template <typename T, typename U>
	requires std::integral<T>&& std::floating_point<U>
	T add(T a, U b) {
		return a + b;
	}
}