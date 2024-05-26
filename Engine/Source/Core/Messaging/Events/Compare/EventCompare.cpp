#include "Pch.h"
#include "EventCompare.h"
#include "../Base/Event.h"


namespace Hi_Engine
{
	bool EventCompare::operator()(const BaseEvent* lhs, const BaseEvent* rhs)
	{
		return lhs->GetPriority() < rhs->GetPriority();
	}
}