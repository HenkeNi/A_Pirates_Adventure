#include "Pch.h"
#include "Dispatcher.h"
#include "Messaging/Events/Event.h"
#include "Messaging/Listener/EventListener.h"


namespace Hi_Engine
{
	Dispatcher& Dispatcher::GetInstance() 
	{
		static Dispatcher instance;
		return instance;
	}

	void Dispatcher::Subscribe(EventListener* aSubscriber)
	{
		auto it = std::find(m_listeners.begin(), m_listeners.end(), aSubscriber);
		assert(it == m_listeners.end());

		m_listeners.push_back(aSubscriber);
	}

	void Dispatcher::Unsubscribe(EventListener* aSubscriber)
	{
		auto it = std::find(m_listeners.begin(), m_listeners.end(), aSubscriber);
		assert(it != m_listeners.end());

		m_listeners.erase(it);
	}

	void Dispatcher::DispatchEvents() 
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

	void Dispatcher::SendEventInstantly(BaseEvent* anEvent)
	{
		BroadcastEvent(anEvent);
	}

	bool Dispatcher::IsQueueFull() const
	{
		return false;
	}

	void Dispatcher::BroadcastEvent(BaseEvent* anEvent)
	{
		assert(anEvent && "Event is not valid!");

		for (auto& listener : m_listeners)
		{
			if (anEvent->IsHandled())
				break;

			anEvent->Dispatch(*listener);
		}
	}
}