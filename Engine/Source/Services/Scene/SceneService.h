#pragma once
#include "../IService.h"
//#include "SceneRegistry.h" MAYBE!??
#include "SceneTypes.h"

namespace Hi_Engine
{
	class Scene;

	// TODO; SceneFactory? (needed?)

	class SceneService : public IService
	{
	public:
		SceneService() = default;
		~SceneService() = default;

		SceneService(const SceneService&) = delete;
		SceneService(SceneService&&) = default;

		SceneService& operator=(const SceneService&) = delete;
		SceneService& operator=(SceneService&&) = default;

		template <DerivedFrom<Scene> T>
		void Insert(std::shared_ptr<Scene> scene);

		template <DerivedFrom<Scene> T, typename... Args>
		void Emplace(Args&&... args);

		template <DerivedFrom<Scene>... Ts> // renme SetActiveScene instead?
		void Init();

		// templated instead??
		void Init(std::initializer_list<SceneID> scenes);
		void Shutdown() override;

		[[nodiscard]] std::weak_ptr<const Scene> GetActive() const;
		[[nodiscard]] std::weak_ptr<Scene> GetActive();

		template <DerivedFrom<Scene> T> // TEST
		void TransitionTo();

		void TransitionTo(SceneID id);
		void Push(SceneID id);
		void Pop();
		void SwapTo(SceneID id);

	private:
		void LoadScene(SceneID id);

		using SceneMap = std::unordered_map<SceneID, std::shared_ptr<Scene>>; // replace with unique_ptr?

		SceneMap m_scenes;
		std::vector<SceneID> m_activeScenes; // stack instead? or not (cant see behind current)
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
	void SceneService::Emplace(Args&&... args)
	{
		const SceneID id = GetSceneID<T>(); 

		m_scenes.insert_or_assign(id, std::make_shared<T>(std::forward<Args>(args)...));
		//m_nameToID.insert_or_assign(name, id);

		m_scenes[id]->OnCreated();
	}

	template <DerivedFrom<Scene>... Ts>
	void SceneService::Init()
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