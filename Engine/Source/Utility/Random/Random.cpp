#include "Pch.h"
#include "Random.h"

namespace Random
{
	int InRange(int min, int max)
	{
		static std::random_device rd; // do elsewhere... (in engine??)
		static std::mt19937 gen(rd());

		std::uniform_int_distribution<int> dis(min, max);
		return dis(gen);
	}

}