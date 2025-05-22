#include "Pch.h"
#include "System.h"

namespace Hi_Engine
{
	System::System(World& ecs)
		: m_ecs{ ecs }, m_isEnabled{ true }
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