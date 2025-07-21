#pragma once
#include "System.h"
#include "Services/Resource/ResourceAliases.h"

namespace Hi_Engine
{
	// Lazy loading? only load/insert audio source into resource service when first used

	// AudioSystem (or all systems) are game side; listens to event

	// Add Get Entity function to world (returns a handle)?

	class AudioService;

	class AudioSystem : public System, public EventListener
	{
	public:
		AudioSystem(World& world, std::weak_ptr<AudioService> audioService, std::weak_ptr<AudioAssetService> audioAssetService);
		
		void OnEvent(class PlaySoundEvent& event) override;
		void OnEvent(class StopSoundEvent& event) override;
		void OnEvent(class SetVolumeEvent& event) override;

	private:
		std::weak_ptr<AudioService> m_audioService;
		std::weak_ptr<AudioAssetService> m_audioAssetService;
	};
}