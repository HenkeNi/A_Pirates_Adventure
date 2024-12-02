#include "Pch.h"
#include "DebugEvents.h"

namespace Hi_Engine
{
	CreateImGuiWindowRequest::CreateImGuiWindowRequest()
		: Event{ ePriority::Moderate }
	{
	}

	void CreateImGuiWindowRequest::Init(const ImGuiWindow& window)
	{
		m_window = window;
	}

	void CreateImGuiWindowRequest::Dispatch(EventListener& listener)
	{
		listener.HandleEvent(*this);
	}
}
