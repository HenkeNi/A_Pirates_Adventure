#include "Pch.h"
#include "EventDispatcher.h"
#include "EventListener.h"


namespace Hi_Engine
{
	EventDispatcher& EventDispatcher::GetInstance() 
	{
		static EventDispatcher instance;
		return instance;
	}

	void EventDispatcher::Subscribe(EventListener* subscriber)
	{
		auto it = std::find(m_listeners.begin(), m_listeners.end(), subscriber);
		assert(it == m_listeners.end());

		m_listeners.push_back(subscriber);
	}

	void EventDispatcher::Unsubscribe(EventListener* subscriber)
	{
		auto it = std::find(m_listeners.begin(), m_listeners.end(), subscriber);
		assert(it != m_listeners.end());

		m_listeners.erase(it);
	}

	void EventDispatcher::DispatchEvents() 
	{
		while (!m_events.empty())
		{
			if (auto* event = m_events.top())
			{
				BroadcastEvent(event);				
				event->Reset();

				delete event;
			}
			m_events.pop();
		}
	} 

	void EventDispatcher::SendEventInstantly(BaseEvent* event)
	{
		BroadcastEvent(event);
	}

	bool EventDispatcher::IsQueueFull() const
	{
		return false;
	}

	void EventDispatcher::BroadcastEvent(BaseEvent* event)
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