#pragma once
#include "System.h"

namespace Hi_Engine
{
	class AudioService;

	class AudioSystem : public System
	{
	public:
		AudioSystem(World& world, std::weak_ptr<AudioService> audioService);
		
		eUpdatePhase GetUpdatePhase() const override;

	private:
		std::weak_ptr<AudioService> m_audioService; // weak ptr instead?
	};
}