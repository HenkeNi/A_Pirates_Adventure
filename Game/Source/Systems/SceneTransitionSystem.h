#pragma once
#include <../Source/ECS/Systems/System.h>

// TODO; consider replacing reference to SceneManager with event?

class SceneManager;

namespace Hi_Engine
{
	class ECSCoordinator;
}

class SceneTransitionSystem : public Hi_Engine::System
{
public:
	SceneTransitionSystem(Hi_Engine::ECSCoordinator& ecs, SceneManager& manager);

	void Update(float deltaTime) override;
	Hi_Engine::eUpdatePhase GetUpdatePhase() const override;

private:
	SceneManager& m_sceneManager;
};

