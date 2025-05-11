#pragma once
//#include "PostMaster/Subscriber.h"
#include "Services/IService.h"
//#include "Scene.h"


//namespace Utility
//{
//	using Scenes = std::unordered_map<eScene, std::shared_ptr<Scene>>;
//}

namespace Hi_Engine
{
	// Consider; read scenes from file?

	class Scene;

	class SceneManager : public IService // public Subscriber
	{
	public:
		using SceneID = uint32_t;

		SceneManager();
		~SceneManager();

		//void Receive(Message& message) override;

		template <typename T, typename... Args>
		void Register(const char* name, Args&&... args); // AddScene?

		void Init(const std::initializer_list<SceneID>& scenes);
		void Shutdown();

		std::weak_ptr<const Scene> GetActive() const;
		std::weak_ptr<Scene> GetActive();

		void TransitionTo(SceneID id);
		void Push(SceneID id);
		void Pop();
		void SwapTo(SceneID id);

	private:
		void LoadScene(SceneID id);

		std::unordered_map<SceneID, std::shared_ptr<Scene>> m_registeredScenes; // have a unique?
		// name to id?

		// Utility::Scenes m_registeredScenes;
		std::vector<SceneID> m_activeScenes;
	};

#pragma region Method_Definitions

	template <typename T, typename... Args>
	void SceneManager::Register(const char* name, Args&&... args)
	{
		m_registeredScenes.insert({ name, std::make_shared<T>(std::forward<Args>(args)...) });
		m_registeredScenes[name]->OnCreated();
	}

#pragma endregion Method_Definitions
}