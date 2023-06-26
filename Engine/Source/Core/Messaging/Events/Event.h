#pragma once
#include "../Data/Enumerations.h"

namespace Hi_Engine
{
	class EventListener;

	class Event
	{
	public:
		Event(ePriority aPriority = ePriority::Moderate);
		virtual	~Event() = default;

		virtual void	Dispatch(EventListener& aListener)	  = 0;
		virtual void	Destroy()							  = 0;
		virtual void	Clean()								  = 0;

		ePriority		GetPriority()						const;
		bool			IsHandled()							const;
		void			HandleEvent();

	protected:
		friend struct	EventCompare;

		ePriority		m_priority;
		bool			m_isHandled;
	};
}