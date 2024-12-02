#pragma once

namespace UtilityFunctions
{
	glm::vec2 ScreenToWorldCoordinates(const glm::vec2& position);


	// TODO; create a NoiseManager???
	float GetTerrainNoise(float xPos, float yPos);

	float GetWeatherNoise(float time);
}



//FVector4 TimeSystem::CalculateDaylightColor(Entity* worldTimeEntity)
//{
//	// put elsewhere????
//	static std::unordered_map<eTimeOfDay, FVector4> daylights;
//	daylights.insert(std::make_pair(eTimeOfDay::Dawn, FVector4{ 0.9804f,	0.7725f,	0.5529f,	1.f }));
//	//daylights.insert(std::make_pair(eTimeOfDay::Day, FVector4{ 0.9569f,	0.8471f,	0.6706f,	1.f }));
//	daylights.insert(std::make_pair(eTimeOfDay::Day, FVector4{ 1.f,	1.f,	1.f,	1.f }));
//	daylights.insert(std::make_pair(eTimeOfDay::Dusk, FVector4{ 0.89f,		0.68f,		0.42f,		1.f }));
//	daylights.insert(std::make_pair(eTimeOfDay::Night, FVector4{ 0.3f,	0.3f,		0.3f,		1.f }));
//
//	if (worldTimeEntity)
//	{
//		if (auto* worldTimeComponent = worldTimeEntity->GetComponent<WorldTimeComponent>())
//		{
//			float progress = worldTimeComponent->CurrentDayProgress;
//			//return Hi_Engine::Lerp(daylights.at(eTimeOfDay::Day), daylights.at(eTimeOfDay::Night), progress);
//			return { 1.f, 1.f, 1.f, 1.f };
//		}
//	}
//
//	return FVector4();
//}
