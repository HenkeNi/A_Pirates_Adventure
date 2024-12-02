#pragma once

namespace Hi_Engine::Math
{
	template <typename T>
	struct Range
	{
		T Min;
		T Max;
	};

	template <typename T>
	T MapToNewRange(const T& value, const Range<T>& oldRange, const Range<T>& newRange)
	{
		T normalized = (value - oldRange.Min) / (oldRange.Max - oldRange.Min);
		T mapped = normalized * (newRange.Max - newRange.Min) + newRange.Min;
	
		return mapped;
	}

	//template <typename T>
	//bool RangeContains(const T& value, const Range<T>& range)
	//{
	//	return value >= range.Min && range <= range.Max;
	//}
}