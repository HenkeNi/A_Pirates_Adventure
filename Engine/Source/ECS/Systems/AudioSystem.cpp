#include "Pch.h"
#include "AudioSystem.h"
#include "Services/Audio/AudioService.h"

namespace Hi_Engine
{
	AudioSystem::AudioSystem(World& world, std::weak_ptr<AudioService> audioService, std::weak_ptr<AudioAssetService> audioAssetService)
		: System{ world, eUpdatePhase::PostUpdate }, m_audioService{ audioService }, m_audioAssetService{ audioAssetService }
	{
	}

	void AudioSystem::OnEvent(PlaySoundEvent& event)
	{
		if (auto audioService = m_audioService.lock())
		{
			// audioService->PlaySound(event);
		}
	}

	void AudioSystem::OnEvent(StopSoundEvent& event)
	{

	}

	void AudioSystem::OnEvent(SetVolumeEvent& event)
	{

	}
}