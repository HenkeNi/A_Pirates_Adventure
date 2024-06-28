#include "Pch.h"
#include "NoiseGenerator.h"


namespace Hi_Engine
{
	std::unique_ptr<FastNoiseLite> NoiseGenerator::s_fastNoise = nullptr;

	float NoiseGenerator::GetNoise(float x, float y)
	{
		float noise = s_fastNoise->GetNoise(x, y);
		return noise;
	}

	void NoiseGenerator::SetFrequency(float frequency)
	{
		s_fastNoise->SetFrequency(frequency);
	}

	void NoiseGenerator::SetNoiseType(int type)
	{
		s_fastNoise->SetNoiseType((FastNoiseLite::NoiseType)type);
	}

	void NoiseGenerator::Init()
	{
		s_fastNoise = std::make_unique<FastNoiseLite>();

		s_fastNoise->SetNoiseType(FastNoiseLite::NoiseType_Perlin);
		s_fastNoise->SetFrequency(1.f);
	}
}