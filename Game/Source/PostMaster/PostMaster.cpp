#include "Pch.h"
#include "PostMaster.h"
#include "Message.h"
#include "Subscriber.h"


PostMaster& PostMaster::GetInstance()
{
	static PostMaster instance;
	return instance;
}

void PostMaster::Subscribe(const eMessage aMsgType, Subscriber* aSubscriber)
{
	auto it = std::find(m_subscribers[aMsgType].begin(), m_subscribers[aMsgType].end(), aSubscriber);
	assert(it == m_subscribers[aMsgType].end());

	m_subscribers[aMsgType].push_back(aSubscriber);
}

void PostMaster::Unsubscribe(const eMessage aMsgType, Subscriber* aSubscriber)
{
	auto it = std::find(m_subscribers[aMsgType].begin(), m_subscribers[aMsgType].end(), aSubscriber);
	assert(it != m_subscribers[aMsgType].end());

	m_subscribers[aMsgType].erase(it);
}

void PostMaster::SendMessage(Message aMessage)
{
	for (auto& subsriber : m_subscribers[aMessage.GetMessageType()])
	{
		if (aMessage.IsHandled())
			break;

		subsriber->Receive(aMessage);
	}
}