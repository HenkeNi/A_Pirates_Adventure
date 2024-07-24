#pragma once
#include "ECSTypes.h"

class System;

class SystemManager
{
public:
	SystemManager();
	~SystemManager();

	//template <typename T>
	//void SetSignature(const Signature& signature);
	void AddSystem(System* system);

	void Update(float deltaTime);
	void LateUpdate(float deltaTime);
	void Draw()	const;
	
	void Clear();

private:
	std::vector<System*> m_systems; // TODO; replace with unique ptr
};
//
//#pragma region Method_Definitions
//
//template<typename T>
//inline void SystemManager::SetSignature(const Signature& signature)
//{
//	auto system = std::find_if(m_systems.begin(), m_systems.end(), [&](const System* system) 
//		{
//			return dynamic_cast<T*>(system) != nullptr;
//		});
//
//	if (system != m_systems.end())
//	{
//		system->SetSignature(signature);
//	}
//	else
//	{
//		assert(false && "[SystemManager - ERROR]: System not found!");
//	}
//}
//
//#pragma endregion Method_Definitions 