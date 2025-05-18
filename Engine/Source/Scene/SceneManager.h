#pragma once
#include "../Service/IService.h"

namespace Hi_Engine
{
	class Scene;

	class SceneManager : public IService
	{
	public:
		using SceneID = uint32_t;

		SceneManager() = default;
		~SceneManager() = default;

		SceneManager(const SceneManager&) = delete;
		SceneManager(SceneManager&&) = default;

		SceneManager& operator=(const SceneManager&) = delete;
		SceneManager& operator=(SceneManager&&) = default;

		template <DerivedFrom<Scene> T>
		void Insert(std::shared_ptr<Scene> scene, const char* name);

		template <DerivedFrom<Scene> T, typename... Args>
		void Emplace(const char* name, Args&&... args);

		void Init(std::initializer_list<SceneID> scenes);
		void Shutdown();

		std::weak_ptr<const Scene> GetActive() const;
		std::weak_ptr<Scene> GetActive();

		void TransitionTo(SceneID id);
		void Push(SceneID id);
		void Pop();
		void SwapTo(SceneID id);

		template <DerivedFrom<Scene> T>
		SceneID GetSceneID() const;

	private:
		SceneID GenerateSceneID() const;
		void LoadScene(SceneID id); // path instead?

		using SceneMap = std::unordered_map<SceneID, std::shared_ptr<Scene>>; // replace with unique_ptr?
		using SceneNameMap = std::unordered_map<std::string, SceneID>;

		SceneMap m_scenes;
		SceneNameMap m_nameToID;		
		std::vector<SceneID> m_activeScenes; // stack instead? or not (cant see behind current)
	};

#pragma region Method_Definitions

	template <DerivedFrom<Scene> T>
	void SceneManager::Insert(std::shared_ptr<Scene> scene, const char* name)
	{
		const SceneID id = GetSceneID<T>();

		m_scenes.insert_or_assign(id, std::move(scene));
		m_nameToID.insert_or_assign(name, id);

		m_scenes[id]->OnCreated();
	}

	template <DerivedFrom<Scene> T, typename... Args>
	void SceneManager::Emplace(const char* name, Args&&... args)
	{
		const SceneID id = GetSceneID<T>();

		m_scenes.insert_or_assign(id, std::make_shared<T>(std::forward<Args>(args)...));
		m_nameToID.insert_or_assign(name, id);

		m_scenes[id]->OnCreated();
	}

	template <DerivedFrom<Scene> T>
	SceneManager::SceneID SceneManager::GetSceneID() const
	{
		static const SceneID id = GenerateSceneID();
		return id;
	}

#pragma endregion Method_Definitions
}