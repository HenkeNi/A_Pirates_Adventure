#pragma once
//#include "Math/Vectors/Vector.hpp" // REMOVE!!!
//#include "Utility/Math/Vectors/Vector.hpp"

namespace Hi_Engine
{
	template <typename T>
	struct HitResult
	{
		bool			IsColliding = false;
		FVector2	ContactPoint{ 0, 0 };
		//TVector2<T>	ContactPoint{ 0, 0 };
		FVector2	ContactNormal{ 0, 0 };
		//TVector2<T>	ContactNormal{ 0, 0 };

		// Union?
		T ContactTime = 0;	// BEEDED???
		T THitNear = 0;
	};
}