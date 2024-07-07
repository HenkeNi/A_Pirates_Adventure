#include "Pch.h"
#include "Dispatcher.h"
//#include "../Events/Base/Event.h"
#include "Messaging/Listener/EventListener.h"
//#include "../../../Data/Structs.h"


namespace Hi_Engine
{
	Dispatcher& Dispatcher::GetInstance() 
	{
		static Dispatcher instance;
		return instance;
	}

	void Dispatcher::Subscribe(EventListener* subscriber)
	{
		auto it = std::find(m_listeners.begin(), m_listeners.end(), subscriber);
		assert(it == m_listeners.end());

		m_listeners.push_back(subscriber);
	}

	void Dispatcher::Unsubscribe(EventListener* subscriber)
	{
		auto it = std::find(m_listeners.begin(), m_listeners.end(), subscriber);
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

	void Dispatcher::SendEventInstantly(BaseEvent* event)
	{
		BroadcastEvent(event);
	}

	bool Dispatcher::IsQueueFull() const
	{
		return false;
	}

	void Dispatcher::BroadcastEvent(BaseEvent* event)
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