#pragma once
#include "System.h"
#include "Services/Event/SystemEvents.h"
#include "Services/Rendering/RenderTypes.h"
#include "Services/Resource/ResourceAliases.h" // put in PCH instead? (enough?)

namespace Hi_Engine
{
	//class Editor;
	class RenderService;
	class ServiceRegistry;

	class RenderSystem : public System, public EventListener
	{
	public:
		RenderSystem(World& world, ServiceRegistry& registry);

		void OnEvent(class WindowEvent& event) override;
		void Update(float deltaTime) override;

	private:
		using SubtextureHolder = SubtextureAssetService;

		void RenderWorldSprites(SubtextureHolder& textureHolder, RenderService& renderService, const glm::mat4& projection);
		void RenderUISprites(SubtextureHolder& textureHolder, RenderService& renderService, const glm::mat4& projection);
	
		IVector2 m_windowSize;
		std::weak_ptr<RenderService> m_renderService; // Use IRenderer here!s
		std::weak_ptr<SubtextureHolder> m_subtextureAssetService;
		//std::weak_ptr<Editor> m_editor;
	};
}