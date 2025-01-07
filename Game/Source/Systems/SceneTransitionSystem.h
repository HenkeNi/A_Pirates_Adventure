#pragma once
#include <../Source/ECS/Systems/System.h>

// TODO; consider replacing reference to SceneManager with event?

class SceneManager;

namespace Hi_Engine
{
	class ECSCoordinator;
}

class SceneTransitionSystem : public Hi_Engine::System, public Subscriber
{
public:
	SceneTransitionSystem(Hi_Engine::ECSCoordinator& ecs, SceneManager& manager);
	~SceneTransitionSystem();

	void Update(float deltaTime) override;
	void Receive(Message& message) override;

	Hi_Engine::eUpdatePhase GetUpdatePhase() const override;

private:
	SceneManager& m_sceneManager;
};