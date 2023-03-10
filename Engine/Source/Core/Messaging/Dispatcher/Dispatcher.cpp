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

	void Dispatcher::SendEvent(Event* anEvent)
	{
		for (auto& listener : m_listeners)
		{
			if (anEvent->IsHandled())
				break;

			anEvent->Dispatch(*listener);
		}
	}


	bool Dispatcher::IsQueueFull() const
	{
		return false;
	}
}