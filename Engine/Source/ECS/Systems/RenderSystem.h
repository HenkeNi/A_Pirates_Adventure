#pragma once
#include "System.h"
#include "Event/Events/SystemEvents.h"
#include "Rendering/RenderTypes.h"

namespace Hi_Engine
{
	class Editor;
	class Renderer;

	class RenderSystem : public System, public EventListener
	{
	public:
		RenderSystem(World& world, std::weak_ptr<Renderer> renderer, std::weak_ptr<Editor> editor, const IVector2& size);

		void OnEvent(class WindowEvent& event) override;
		void Update(float deltaTime) override;

		eUpdatePhase GetUpdatePhase() const override;

	private:
		SpriteBatch CreateSpriteBatch() const;
		SpriteBatch CreateUIBatch() const;

		IVector2 m_windowSize;
		std::weak_ptr<Renderer> m_renderer; // Use IRenderer here!s
		std::weak_ptr<Editor> m_editor;
	};
}