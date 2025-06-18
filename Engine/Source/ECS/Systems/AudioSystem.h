#pragma once
#include "System.h"

namespace Hi_Engine
{
	class AudioController;

	class AudioSystem : public System
	{
	public:
		AudioSystem(World& world, AudioController& audioController);
		
		eUpdatePhase GetUpdatePhase() const override;

	private:
		AudioController& m_audioController; // weak ptr instead?
	};
}