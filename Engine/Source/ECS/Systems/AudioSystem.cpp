#include "Pch.h"
#include "AudioSystem.h"

namespace Hi_Engine
{
	AudioSystem::AudioSystem(World& world, AudioController& audioController)
		: System{ world }, m_audioController{ audioController }
	{
	}

	eUpdatePhase AudioSystem::GetUpdatePhase() const
	{
		return eUpdatePhase::PostUpdate; // handle no update phase?
	}
}
