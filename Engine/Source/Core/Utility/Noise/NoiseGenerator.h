#pragma once

class FastNoiseLite;

namespace Hi_Engine
{
	class NoiseGenerator
	{
	public:
		NoiseGenerator();
		~NoiseGenerator();

		NoiseGenerator(const NoiseGenerator&) = delete;
		NoiseGenerator& operator=(const NoiseGenerator&) = delete;

		NoiseGenerator(NoiseGenerator&&) = default;
		NoiseGenerator& operator=(NoiseGenerator&&) = default;

		void Init(float frequenzy = 1.f, int noiseType = 3);
		float GetNoise(float x, float y);
		
		void SetFrequency(float frequency);
		void SetNoiseType(int type);

	private:
		std::unique_ptr<FastNoiseLite> m_fastNoise;
	};
}