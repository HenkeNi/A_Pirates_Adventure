#pragma once
#include "System.h"

namespace Hi_Engine
{
	class AudioController;

	class AudioSystem : public System
	{
	public:
		AudioSystem(World& ecs, AudioController& audioController);
		
		eUpdatePhase GetUpdatePhase() const override;

	private:
		AudioController& m_audioController;
	};
}