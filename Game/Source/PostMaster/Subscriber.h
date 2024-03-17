#pragma once

class Message;

class Subscriber
{
public:
	virtual void Receive(Message& message) = 0;
};