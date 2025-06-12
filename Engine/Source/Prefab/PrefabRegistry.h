#pragma once
#include "../Service/IService.h"

namespace Hi_Engine
{
	// TODO; rename class Prefab...

	// Consider; Keep as Service? or store in ECSRegistry? Store in ResourceHolder?
	// TODO; [json] Place all prefabs into separate files

	struct PropertyValue : std::variant<
		std::nullptr_t,
		bool,
		int,
		float,
		std::string,
		std::unordered_map<std::string, PropertyValue>,
		std::vector<PropertyValue>>
	{
		using variant::variant; // inherit constructors
	};

	struct Prefab
	{
		//using PropertyValue = std::variant<int, float, bool, std::string, std::any>;
		using ComponentData = std::unordered_map<std::string, PropertyValue>; // rename ComponentProperties??

		std::unordered_map<std::string, ComponentData> Data;
	};

	template <typename T>
	T GetPropertyValueOrDefault(const Prefab::ComponentData& data, const std::string& key, const T& defaultValue) // use auto instead of compdata??
	{
		if (auto it = data.find(key); it != data.end())
		{
			if (auto* val = std::get_if<T>(&it->second))
			{
				return *val;
			}
		}

		return defaultValue;
	}

	class PrefabRegistry : public IService
	{
	public:
		void LoadPrefabs(const std::filesystem::path& path);

		// insert prefab?

		// Create from prefab??


		const Prefab& GetPrefab(const std::string& name) const;

		const Prefab* TryGetPrefab(const std::string& name) const;

	private:
		std::unordered_map<std::string, Prefab> m_prefabs;
	};
}
