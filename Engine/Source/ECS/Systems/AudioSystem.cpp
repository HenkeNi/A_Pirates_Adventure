#include "Pch.h"
#include "AudioSystem.h"

namespace Hi_Engine
{
	AudioSystem::AudioSystem(World& world, std::weak_ptr<AudioService> audioService)
		: System{ world }, m_audioService{ audioService }
	{
	}

	eUpdatePhase AudioSystem::GetUpdatePhase() const
	{
		return eUpdatePhase::PostUpdate; // handle no update phase?
	}
}
