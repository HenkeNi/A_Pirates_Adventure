#pragma once
#include "System.h"
#include "Event/Events/SystemEvents.h"

namespace Hi_Engine
{
	class Editor;
	class Renderer;

	class RenderSystem : public System, public EventListener
	{
	public:
		RenderSystem(ECSCoordinator& ecs, Renderer& renderer, std::weak_ptr<Editor> editor, const IVector2& size);

		void HandleEvent(class WindowEvent& event) override;
		void Update(float deltaTime) override;

		eUpdatePhase GetUpdatePhase() const override;

	private:
		void RenderUI();
		void RenderSprites();

		IVector2 m_windowSize;
		Renderer& m_renderer;
		std::weak_ptr<Editor> m_editor;
	};
}