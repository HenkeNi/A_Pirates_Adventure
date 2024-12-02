#include "Pch.h"
#include "UtilityFunctions.h"


namespace UtilityFunctions
{
	// FIX!
	static Hi_Engine::NoiseGenerator TerrainNoise;
	static Hi_Engine::NoiseGenerator WeatherNoise;

	glm::vec2 ScreenToWorldCoordinates(const glm::vec2& position)
	{
		return {};
	}

	float GetTerrainNoise(float xPos, float yPos)
	{
		// FIX!
		static bool isInitialized = false;
		if (!isInitialized)
		{
			TerrainNoise.Init(0.06f, 3);
			isInitialized = true;
		}

		return TerrainNoise.GetNoise(xPos, yPos);
	}
	float GetWeatherNoise(float time)
	{
		static bool isInitialized = false;
		if (!isInitialized)
		{
			WeatherNoise.Init();
			isInitialized = true;
		}

		return WeatherNoise.GetNoise(time, time); // or x, time?
	}
}