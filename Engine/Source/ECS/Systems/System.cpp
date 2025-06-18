#include "Pch.h"
#include "System.h"

namespace Hi_Engine
{
	System::System(World& world)
		: m_world{ world }, m_isEnabled{ true }
	{
	}

	void System::SetEnabled(bool isEnabled)
	{
		m_isEnabled = isEnabled;
	}

	bool System::IsEnabled() const noexcept
	{
		return m_isEnabled;
	}
}