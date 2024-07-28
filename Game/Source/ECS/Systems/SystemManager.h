#pragma once
#include "ECSTypes.h"

class System;

// listen for entiy constructed, etc??
class SystemManager
{
public:
	SystemManager();
	~SystemManager();

	// register system?

	// set signature

	// get system?

	// entity ddestroyed

	// entity signature changed


	//template <typename T>
	//void SetSignature(const Signature& signature);
	void AddSystem(System* system);

	//void Update(float deltaTime);
	//void LateUpdate(float deltaTime);
	//void Draw()	const;
	
	void Clear();

private:
	// std::unordered_map<std::type_index, System*> m_systems;

	std::vector<System*> m_systems; // TODO; replace with unique ptr

	// store render systems, update systems, later update systems?

	// store signatures here??
};