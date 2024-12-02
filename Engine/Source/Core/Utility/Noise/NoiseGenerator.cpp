#include "Pch.h"
#include "NoiseGenerator.h"


namespace Hi_Engine
{
	NoiseGenerator::NoiseGenerator()
		: m_fastNoise{ nullptr }
	{
	}

	NoiseGenerator::~NoiseGenerator()
	{
	}
	
	float NoiseGenerator::GetNoise(float x, float y)
	{
		float noise = m_fastNoise->GetNoise(x, y);
		return noise;
	}

	void NoiseGenerator::Init(float frequenzy, int noiseType)
	{
		m_fastNoise = std::make_unique<FastNoiseLite>();
		
		m_fastNoise->SetNoiseType(static_cast<FastNoiseLite::NoiseType>(noiseType));
		m_fastNoise->SetFrequency(frequenzy);
	}

	void NoiseGenerator::SetFrequency(float frequency)
	{
		m_fastNoise->SetFrequency(frequency);
	}

	void NoiseGenerator::SetNoiseType(int type)
	{
		m_fastNoise->SetNoiseType((FastNoiseLite::NoiseType)type);
	}
}