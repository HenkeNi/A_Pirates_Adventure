#pragma once
#include <../Source/ECS/Systems/System.h>

// TODO; consider replacing reference to SceneManager with event?

//class SceneManager;

namespace Hi_Engine
{
	class World;
	class SceneService;
}

// Not needed?? send event directly to SceneManager?

class SceneTransitionSystem : public Hi_Engine::System//, public Subscriber
{
public:
	SceneTransitionSystem(Hi_Engine::World& world, Hi_Engine::SceneService& service);
	~SceneTransitionSystem();

	void Update(float deltaTime) override;
	//void Receive(Message& message) override;

	Hi_Engine::eUpdatePhase GetUpdatePhase() const override;

private:
	Hi_Engine::SceneService& m_sceneService;
};