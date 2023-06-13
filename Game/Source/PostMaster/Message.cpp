#include "Pch.h"
#include "Message.h"


Message::Message(eMessage aMsgType, const std::any& someData)
	: m_type{ aMsgType }, m_data{ someData }, m_isHandled{ false }
{
}

eMessage Message::GetMessageType() const
{
	return m_type;
}

const std::any& Message::GetData() const
{
	return m_data;
}

bool Message::IsHandled() const
{
	return m_isHandled;
}

void Message::HandleEvent()
{
	m_isHandled = true;
}