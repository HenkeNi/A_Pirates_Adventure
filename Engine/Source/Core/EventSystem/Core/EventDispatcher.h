#pragma once
// #include "../Events/Compare/EventCompare.h"
#include "Event.h"

// TODO: replace array with Binary Search Tree Set or AVL or SPlay Tree? or map
// TODO; check if sorting after importance works?
#include <queue>

namespace Hi_Engine
{
	class BaseEvent;
	class EventListener;

	//struct EventCompare;

	class EventDispatcher
	{
	public:
		EventDispatcher(const EventDispatcher&)				= delete;
		EventDispatcher& operator=(const EventDispatcher&)	= delete;

		static EventDispatcher& GetInstance();

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
		EventDispatcher() = default;

		bool IsQueueFull() const;
		void BroadcastEvent(BaseEvent* event);
		 
		std::priority_queue<BaseEvent*, std::vector<BaseEvent*>, EventCompare>	m_events;	 // TODO; Own heap or priority queue?
		std::vector<EventListener*>												m_listeners;	
	};

#pragma region Method_Definitions

	template <typename T, typename... Args>
	void EventDispatcher::SendEventInstantly(Args&&... args)
	{
		T* newEvent = new T();
		newEvent->Init(std::forward<Args>(args)...);

		BroadcastEvent(newEvent);
		delete newEvent;
	}

	template <typename T, typename... Args>
	void EventDispatcher::AddEvent(Args&&... args)
	{
		T* newEvent = new T();
		newEvent->Init(std::forward<Args>(args)...);

		m_events.push(newEvent);
	}

	template <typename T>
	void EventDispatcher::AddEvent()
	{
		T* newEvent = new T();
		m_events.push(newEvent);
	}

#pragma endregion Method_Definitions
}