#include "Pch.h"
#include "AudioSystem.h"

namespace Hi_Engine
{
	AudioSystem::AudioSystem(ECSCore& ecs, AudioController& audioController)
		: System{ ecs }, m_audioController{ audioController }
	{
	}

	eUpdatePhase AudioSystem::GetUpdatePhase() const
	{
		return eUpdatePhase::PostUpdate; // handle no update phase?
	}
}
