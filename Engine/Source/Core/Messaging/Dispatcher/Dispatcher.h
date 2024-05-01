#pragma once
#include "../../../Data/Structs.h"

// TODO: replace array with Binary Search Tree Set or AVL or SPlay Tree? or map
// TODO; check if sorting after importance works?

// Todo: rename EventSystem?? or MessageSystem??
namespace Hi_Engine
{
	class BaseEvent;
	class EventListener;

	class Dispatcher
	{
	public:
		Dispatcher(const Dispatcher&)				= delete;
		Dispatcher& operator=(const Dispatcher&)	= delete;

		static Dispatcher& GetInstance();

		void Subscribe(EventListener* subscriber);
		void Unsubscribe(EventListener* subscriber);

		void DispatchEvents();	// Rename Broadcast or BroadcastEvents?
			
		template <typename T, typename... Args>
		void SendEventInstantly(Args&&... args);			
		void SendEventInstantly(BaseEvent* event);			

		template <typename T, typename... Args>
		void AddEvent(Args&&... args);

		template <typename T>
		void AddEvent();		// rename, or take in pointer?

	private:
		Dispatcher() = default;

		bool IsQueueFull() const;
		void BroadcastEvent(BaseEvent* event);
		 
		std::priority_queue<BaseEvent*, std::vector<BaseEvent*>, EventCompare>	m_events;	 // TODO; Own heap or priority queue?
		std::vector<EventListener*>												m_listeners;	
	};

#pragma region Method_Definitions

	template <typename T, typename... Args>
	void Dispatcher::SendEventInstantly(Args&&... args)
	{
		T* newEvent = new T();
		newEvent->Init(std::forward<Args>(args)...);

		BroadcastEvent(newEvent);
		delete newEvent;
	}

	template <typename T, typename... Args>
	void Dispatcher::AddEvent(Args&&... args)
	{
		T* newEvent = new T();
		newEvent->Init(std::forward<Args>(args)...);

		m_events.push(newEvent);
	}

	template <typename T>
	void Dispatcher::AddEvent()
	{
		T* newEvent = new T();
		m_events.push(newEvent);
	}

#pragma endregion Method_Definitions
}