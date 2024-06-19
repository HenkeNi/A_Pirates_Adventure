#include "Pch.h"
#include "Random.h"


namespace Hi_Engine
{
	int GetWeightedRandomIndex(const std::vector<double>& weights)
	{
		std::discrete_distribution<int> dist(weights.begin(), weights.end());

		int index = dist(gen);
		return index;
	}
}