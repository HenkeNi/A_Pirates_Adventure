#include "Pch.h"
#include "ServiceLocator.h"


namespace Hi_Engine
{
	//std::weak_ptr<AudioController> ServiceLocator::GetAudioController()
	//{
	//	return s_audioController;
	//}

	//void ServiceLocator::Register(std::weak_ptr<AudioController> controller)
	//{
	//	s_audioController = controller;
	//}


	void ServiceLocator::Register(std::weak_ptr<Window> window)
	{
		s_window = window;
	}

	void ServiceLocator::Register(std::weak_ptr<PhysicsEngine> physics)
	{
		s_physics = physics;
	}

	std::weak_ptr<Window> ServiceLocator::GetWindow()
	{
		return s_window;
	}

	std::weak_ptr<PhysicsEngine> ServiceLocator::GetPhysics()
	{
		return s_physics;
	}

}
