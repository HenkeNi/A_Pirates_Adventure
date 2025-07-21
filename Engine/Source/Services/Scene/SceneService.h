#pragma once
#include "../IService.h"
#include "SceneTypes.h"

namespace Hi_Engine
{
	class Scene;

	// Consider; using unique ptrs? Use a ForEach in that case?
	// Consider; using a stack for active scenes instead? or not (cant see behind current)
	// Rename Insert & Emplace to AddScene and CreateScene?

	class SceneService : public IService
	{
	public:
		SceneService() = default;
		~SceneService() = default;

		SceneService(const SceneService&) = delete;
		SceneService(SceneService&&) = default;

		SceneService& operator=(const SceneService&) = delete;
		SceneService& operator=(SceneService&&) = default;

		// ==================== Management ====================
		template <DerivedFrom<Scene> T>
		void Insert(std::shared_ptr<Scene> scene);

		template <DerivedFrom<Scene> T, typename... Args>
		T& Emplace(Args&&... args);

		template <DerivedFrom<Scene> T>
		void Remove();

		void Clear();

		// ==================== Activation ====================
		template <DerivedFrom<Scene>... Ts>
		void SetActiveScenes();

		void SetActiveScenes(std::initializer_list<SceneID> scenes);

		// ==================== Transitions ====================
		template <DerivedFrom<Scene> T>
		void TransitionTo();

		void TransitionTo(SceneID id);

		void Push(SceneID id);

		void Pop();

		void SwapTo(SceneID id);

		// ==================== Queries ====================
		[[nodiscard]] std::weak_ptr<const Scene> GetActive() const;

		[[nodiscard]] std::weak_ptr<Scene> GetActive();

		// ==================== Service Overrides ====================
		void Shutdown() noexcept override;

	private:
		// ==================== Type Aliases ====================
		using SceneMap = std::unordered_map<SceneID, std::shared_ptr<Scene>>;

		// ==================== Data Members ====================
		SceneMap m_scenes;
		std::vector<SceneID> m_activeScenes; 
	};

#pragma region Method_Definitions

	template <DerivedFrom<Scene> T>
	void SceneService::Insert(std::shared_ptr<Scene> scene)
	{
		const SceneID id = GetSceneID<T>();

		m_scenes.insert_or_assign(id, std::move(scene));
		//m_sceneInfo.insert_or_assign(name, { id, "" });

		m_scenes[id]->OnCreated();
	}

	template <DerivedFrom<Scene> T, typename... Args>
	T& SceneService::Emplace(Args&&... args)
	{
		const SceneID id = GetSceneID<T>(); 

		auto scene = std::make_shared<T>(std::forward<Args>(args)...);
		m_scenes.insert_or_assign(id, scene);
		//m_nameToID.insert_or_assign(name, id);

		m_scenes[id]->OnCreated();

		return *scene;
	}

	template <DerivedFrom<Scene> T>
	void SceneService::Remove()
	{
		const SceneID id = GetSceneID<T>();

		UnloadScene(id);

		m_activeScenes.erase(std::remove(m_activeScenes.begin(), m_activeScenes.end(), id), m_activeScenes.end());
		m_scenes.erase(id);
	}

	template <DerivedFrom<Scene>... Ts>
	void SceneService::SetActiveScenes()
	{
		m_activeScenes.push_back(GetSceneID<Ts>()...);
	}

	template <DerivedFrom<Scene> T>
	void SceneService::TransitionTo()
	{
		TransitionTo(GetSceneID<T>());
	}

#pragma endregion Method_Definitions
}