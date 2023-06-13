#pragma once
#include "../Data/Enumerations.h"

class Message;
class Subscriber;

class PostMaster
{
public:
	PostMaster(const PostMaster&)			 = delete;
	PostMaster& operator=(const PostMaster&) = delete;
	
	static PostMaster&	GetInstance();

	void				Subscribe(const eMessage aMsgType, Subscriber* aSubscriber);
	void				Unsubscribe(const eMessage aMsgType, Subscriber* aSubscriber);
	void				SendMessage(Message aMessage);

private:
	PostMaster() = default;

	std::unordered_map<eMessage, std::vector<Subscriber*>> m_subscribers; 
};
