#pragma once
#include "ECSTypes.h"

class System;

// listen for entiy constructed, etc??
class SystemManager
{
public:
	SystemManager();
	~SystemManager();

	template <typename T>
	void RegisterSystem(const char* name);

	template <typename T>
	std::weak_ptr<System> GetSystem();
	
	std::weak_ptr<System> GetSystem(const char* system);

	// std::type_index GetSystemType(const char* system) const;

	template <typename T>
	void SetSignature(const Signature& signature); // FIX! signature is map!

	template <typename T>
	Signatures GetSignature() const;

	template <typename T>
	bool HasSystem() const;

	// events; entity ddestroyed & entity signature changed

	void RemoveAllSystem();

private:
	std::unordered_map<std::type_index, std::shared_ptr<System>> m_systems;
	std::unordered_map<std::string, std::type_index> m_systemTypes;

	// store render systems, update systems?
};

#pragma region Method_Definitions

template<typename T>
inline void SystemManager::RegisterSystem(const char* name)
{
	auto type = std::type_index(typeid(T));

	m_systems.insert({ type, std::make_shared<T>() });
	m_systemTypes.insert({ name, type });
}

template<typename T>
inline std::weak_ptr<System> SystemManager::GetSystem()
{
	auto type = std::type_index(typeid(T));

	auto itr = m_systems.find(type);
	if (itr != m_systems.end())
	{
		return itr->second;
	}

	return std::weak_ptr<System>();
}

template<typename T>
inline void SystemManager::SetSignature(const Signature& signature)
{
	auto type = std::type_index(typeid(T));

	auto itr = m_systems.find(type);
	if (itr != m_systems.end())
	{
		// itr->second->SetSignature(signature);
	}
}

template<typename T>
inline Signatures SystemManager::GetSignature() const
{
	auto type = std::type_index(typeid(T));

	auto itr = m_systems.find(type);
	if (itr != m_systems.end())
	{
		return itr->second->m_signatures;
	}

	return Signature();
}

template<typename T>
inline bool SystemManager::HasSystem() const
{
	auto type = std::type_index(typeid(T));
	bool found = m_systems.find(type) != m_systems.end();
	
	return found;
}

#pragma endregion Method_Definitions