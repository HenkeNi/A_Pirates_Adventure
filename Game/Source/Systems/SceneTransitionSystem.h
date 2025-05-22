#pragma once
#include <../Source/ECS/Systems/System.h>

// TODO; consider replacing reference to SceneManager with event?

class SceneManager;

namespace Hi_Engine
{
	class World;
	class SceneManager;
}

class SceneTransitionSystem : public Hi_Engine::System, public Subscriber
{
public:
	SceneTransitionSystem(Hi_Engine::World& world, Hi_Engine::SceneManager& manager);
	~SceneTransitionSystem();

	void Update(float deltaTime) override;
	void Receive(Message& message) override;

	Hi_Engine::eUpdatePhase GetUpdatePhase() const override;

private:
	Hi_Engine::SceneManager& m_sceneManager;
};