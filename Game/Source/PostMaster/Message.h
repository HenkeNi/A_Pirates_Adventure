#pragma once
#include "../Data/Enumerations.h"

class Message
{
public:
	Message(eMessage aMsgType, const std::any& someData);
	virtual	~Message() = default;

	eMessage			GetMessageType()	const;
	const std::any&		GetData()			const;
	bool				IsHandled()			const;
	void				HandleEvent();

private:
	std::any			m_data;
	eMessage			m_type;
	bool				m_isHandled;

	// is repeating?!
};
