#pragma once

// Use alias for vector2 instead??

namespace Hi_Engine::Math
{
	template <typename T>
	struct Point
	{
		T X;
		T Y;
	};

	template <typename T>
	Point(T x, T y) -> Point<T>;
}