#include "Pch.h"
#include "Event.h"

namespace Hi_Engine
{
	Event::Event(ePriority aPriority)
		: m_priority{ aPriority }, m_isHandled{ false }
	{
	}

	bool Event::IsHandled() const
	{
		return m_isHandled;
	}

	void Event::HandleEvent()
	{
		m_isHandled = true;
	}
}