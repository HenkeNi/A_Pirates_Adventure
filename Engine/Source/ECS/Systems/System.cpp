#include "Pch.h"
#include "System.h"

namespace Hi_Engine
{
	System::System(World& world, eUpdatePhase phase)
		: m_world{ world }, m_updatePhase{ phase }, m_isEnabled{ true }
	{
	}

	void System::Enable()
	{
		if (!m_isEnabled)
		{
			m_isEnabled = true;
			OnEnabled();
		}
	}

	void System::Disable()
	{
		if (m_isEnabled)
		{
			m_isEnabled = false;
			OnDisabled();
		}
	}
}