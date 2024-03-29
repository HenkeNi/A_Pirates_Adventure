#pragma once

class Message;
class Subscriber;

enum class eMessage;

class PostMaster
{
public:
	PostMaster(const PostMaster&)			 = delete;
	PostMaster& operator=(const PostMaster&) = delete;
	
	static PostMaster& GetInstance();

	void Subscribe(const eMessage messageType, Subscriber* subscriber);
	void Unsubscribe(const eMessage messageType, Subscriber* subscriber);
	void SendMessage(Message message);

private:
	PostMaster() = default;

	std::unordered_map<eMessage, std::vector<Subscriber*>> m_subscribers; 
};
