#pragma once


class FastNoiseLite;

namespace Hi_Engine
{
	class Engine;

	class NoiseGenerator
	{
	public:
		static float GetNoise(float x, float y);
		
		static void SetFrequency(float frequency);
		static void SetNoiseType(int type);

	private:
		static void Init();

		friend class Engine;

		static std::unique_ptr<FastNoiseLite> s_fastNoise;
	};
}