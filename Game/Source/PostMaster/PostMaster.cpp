#include "Pch.h"
#include "PostMaster.h"
#include "Message.h"
#include "Subscriber.h"


PostMaster& PostMaster::GetInstance()
{
	static PostMaster instance;
	return instance;
}

void PostMaster::Subscribe(const eMessage messageType, Subscriber* subscriber)
{
	auto it = std::find(m_subscribers[messageType].begin(), m_subscribers[messageType].end(), subscriber);
	assert(it == m_subscribers[messageType].end());

	m_subscribers[messageType].push_back(subscriber);
}

void PostMaster::Unsubscribe(const eMessage messageType, Subscriber* subscriber)
{
	auto it = std::find(m_subscribers[messageType].begin(), m_subscribers[messageType].end(), subscriber);
	assert(it != m_subscribers[messageType].end());

	m_subscribers[messageType].erase(it);
}

void PostMaster::SendMessage(Message message)
{
 	for (auto& subsriber : m_subscribers[message.GetMessageType()])
	{
		if (message.IsHandled())
			break;

		subsriber->Receive(message);
	}
}