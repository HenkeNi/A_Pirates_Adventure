#pragma once
#include "Utility/IDGenerator.h"
#include <cstdint>

namespace Hi_Engine
{
	struct EventTag final {};

	using EventID = uint32_t;

	template <typename T> // TODO; specify concept for Events...
	EventID GetEventID()
	{
		return IDGenerator<EventTag>::GetID<T>();
	}
}