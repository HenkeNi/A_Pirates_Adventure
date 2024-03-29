#pragma once

enum class eMessage;

class Message
{
public:
	Message(eMessage messageType, const std::any& data);
	virtual	~Message() = default;

	eMessage			GetMessageType()	const;
	const std::any&		GetData()			const;
	bool				IsHandled()			const;
	void				HandleMessage();

private:
	std::any			m_data;
	eMessage			m_type;
	bool				m_isHandled;

	// is repeating?!
};

