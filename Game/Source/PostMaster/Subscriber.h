#pragma once

class Message;

class Subscriber
{
public:
	virtual void Receive(Message& aMsg) = 0;
};