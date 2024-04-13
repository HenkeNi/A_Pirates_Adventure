#include "Pch.h"
#include "ServiceLocator.h"


namespace Hi_Engine
{
	AudioController* ServiceLocator::s_audioController = nullptr;

	AudioController* ServiceLocator::GetAudioController()
	{
		return s_audioController;
	}

	void ServiceLocator::Register(AudioController* controller)
	{
		s_audioController = controller;
	}


}
