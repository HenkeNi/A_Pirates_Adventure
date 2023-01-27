#pragma once
#include "Data/Enumerations.h"

namespace Hi_Engine
{
	class EventListener;

	class Event
	{
	public:
		Event(ePriority aPriority = ePriority::Moderate);
		virtual	~Event() = default;

		virtual void	Dispatch(EventListener& aListener) = 0;
		bool			IsHandled()							const;
		void			HandleEvent();

	private:
		ePriority		m_priority;
		bool			m_isHandled;
	};
}