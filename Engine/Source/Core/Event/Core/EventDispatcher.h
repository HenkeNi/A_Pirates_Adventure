#pragma once
#include "Event.h"

// TODO: replace array with Binary Search Tree Set or AVL or SPlay Tree? or map
// TODO; check if sorting after importance works?
#include <queue>

namespace Hi_Engine
{
	class BaseEvent;
	class EventListener;

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

		template <typename T, typename... Args>
		void AddEvent(Args&&... args); // reanem? CreateEvemt`?

	private:
		EventDispatcher() = default;

		bool IsQueueFull() const;
		void BroadcastEvent(BaseEvent* event);
		 
		std::priority_queue<BaseEvent*, std::vector<BaseEvent*>, EventCompare>	m_events;	 // TODO; Own heap or priority queue?
		std::vector<EventListener*>												m_listeners;	
	};

#pragma region Method_Definitions 

	// TODO; use memory pool here?

	template <typename T, typename... Args>
	void EventDispatcher::SendEventInstantly(Args&&... args)
	{
		T* newEvent = new T(std::forward<Args>(args)...);
		///newEvent->Init();

		BroadcastEvent(newEvent);
		delete newEvent;
	}

	template <typename T, typename... Args>
	void EventDispatcher::AddEvent(Args&&... args)
	{
		T* newEvent = new T(std::forward<Args>(args)...);
		//newEvent->Init();

		m_events.push(newEvent);
	}

#pragma endregion Method_Definitions
}