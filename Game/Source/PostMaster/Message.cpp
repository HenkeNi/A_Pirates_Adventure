#include "Pch.h"
#include "Message.h"


Message::Message(eMessage messageType, const std::any& data)
	: m_type{ messageType }, m_data{ data }, m_isHandled{ false }
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

void Message::HandleMessage()
{
	m_isHandled = true;
}