#include "Pch.h"
#include "EventService.h"
#include "EventListener.h"

namespace Hi_Engine
{
	void EventService::Subscribe(EventListener* subscriber)
	{
		auto it = std::find(m_listeners.begin(), m_listeners.end(), subscriber);
		assert(it == m_listeners.end());

		m_listeners.push_back(subscriber);
	}

	void EventService::Unsubscribe(EventListener* subscriber)
	{
		auto it = std::find(m_listeners.begin(), m_listeners.end(), subscriber);
		assert(it != m_listeners.end());

		m_listeners.erase(it);
	}

	void EventService::DispatchEvents()
	{
		while (!m_events.empty())
		{
			if (auto* event = m_events.top())
			{
				BroadcastEvent(event);				
				event->Reset(); // maybe redo, since returning to pool, it should be reset

				delete event;
			}
			m_events.pop();
		}
	}

	bool EventService::IsQueueFull() const
	{
		return false;
	}

	void EventService::BroadcastEvent(BaseEvent* event)
	{
		assert(event && "Event is not valid!");

		for (auto& listener : m_listeners)
		{
			if (event->IsHandled())
				break;

			event->Dispatch(*listener);
		}
	}
}