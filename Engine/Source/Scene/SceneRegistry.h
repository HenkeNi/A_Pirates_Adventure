#pragma once
#include "../Service/IService.h"
#include "Utility/IDGenerator.h"

namespace Hi_Engine
{
	class Scene;

	using SceneID = uint32_t;

	struct SceneTag final {};

	struct SceneRegistryEntry
	{
		SceneID ID;
		std::filesystem::path JsonPath;

		std::string DisplayName;
		std::string Description;

		// thumbnail path? priority?
	};

	template <ComponentType T>
	SceneID GetSceneID()
	{
		return IDGenerator<SceneTag>::GetID<T>();
	}

	class SceneRegistry : public IService
	{
	public:
		template <DerivedFrom<Scene> T, typename... Args>
		void Register(const std::string& name, Args&&... args);

		// templated?

		const SceneRegistryEntry& GetEntry(SceneID id) const;
		const SceneRegistryEntry& GetEntry(const std::string& name) const;

	private:
		std::unordered_map<SceneID, SceneRegistryEntry> m_entries;
		std::unordered_map<std::string, SceneRegistryEntry*> m_nameToEntry;
	};

	template <DerivedFrom<Scene> T, typename... Args>
	void SceneRegistry::Register(const std::string& name, Args&&... args)
	{
		const SceneID id = IDGenerator<SceneTag>::GetID<T>();

		auto [it, success] = m_entries.try_emplace(id, std::forward<Args>(args)...);

		if (success)
		{
			m_nameToEntry.insert({ name, &it->second });
		}
	}
}
