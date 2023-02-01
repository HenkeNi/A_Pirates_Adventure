#pragma once
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
}