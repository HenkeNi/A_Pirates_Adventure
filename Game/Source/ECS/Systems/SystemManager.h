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