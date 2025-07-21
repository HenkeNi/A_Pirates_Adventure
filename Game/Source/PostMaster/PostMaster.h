#pragma once

class Message;
class Subscriber;

enum class eMessage;

// TODO; merge with EventService!?

class PostMaster
{
public:
	PostMaster(const PostMaster&)			 = delete;
	PostMaster& operator=(const PostMaster&) = delete;
	
	static PostMaster& GetInstance();

	void Subscribe(const eMessage messageType, Subscriber* subscriber);
	void Unsubscribe(const eMessage messageType, Subscriber* subscriber);
	void SendMessage(Message message);	// fix, so dont have to send copy (mark is handled prevents)

private:
	PostMaster() = default;

	std::unordered_map<eMessage, std::vector<Subscriber*>> m_subscribers; 
};
