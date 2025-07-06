#pragma once
#include "../IService.h"
#include "Utility/JsonUtils.h"

namespace Hi_Engine
{
	// TODO; store in ResourceHolder?

	// Consider; Keep as Service? or store in ECSRegistry? Store in ResourceHolder?
	// TODO; [json] Place all prefabs into separate files

	//struct PropertyValue : std::variant<
	//	std::nullptr_t,
	//	bool,
	//	int,
	//	float,
	//	std::string,
	//	std::unordered_map<std::string, PropertyValue>,
	//	std::vector<PropertyValue>>
	//{
	//	using variant::variant; // inherit constructors
	//};

	struct Prefab
	{
		//using PropertyValue = std::variant<int, float, bool, std::string, std::any>;
		//using ComponentData = std::unordered_map<std::string, PropertyValue>; // rename ComponentProperties??
		//std::unordered_map<std::string, ComponentData> Data;

		std::unordered_map<std::string, Properties> ComponentProperties;
	};

	// Put in json utils? Next to GetPropertyValue?
	

	class PrefabRegistryService : public IService
	{
	public:
		void LoadPrefabs(const std::filesystem::path& path);

		// insert prefab?

		// Create from prefab??


		[[nodiscard]] const Prefab& GetPrefab(const std::string& name) const;

		[[nodiscard]] const Prefab* TryGetPrefab(const std::string& name) const;

	private:
		std::unordered_map<std::string, Prefab> m_prefabs;
	};
}
