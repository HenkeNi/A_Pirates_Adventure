#pragma once
#include "../IService.h"
#include "Event.h"
// TODO: replace array with Binary Search Tree Set or AVL or SPlay Tree? or map
// TODO; check if sorting after importance works?
#include <queue>

// TODO; user needs to be able to specify events?

namespace Hi_Engine
{
	class BaseEvent;
	class EventListener;


	class EventDispatcher
	{
	public:
		template <typename T>
		void Subscribe()
		{

		}

		template <typename T>
		void Unsubscribe()
		{

		}

	private:
		using Callback = std::function<void(const void*)>;
		std::unordered_map<std::type_index, std::vector<Callback>> m_callbacks; // use EventTag ID (GEnerateID) instead??
	};

	// EvenDispatcher EventService
	class EventService : public IService
	{
	public:
		void Subscribe(EventListener* subscriber);
		void Unsubscribe(EventListener* subscriber);

		void DispatchEvents();	// Rename Broadcast or BroadcastEvents?
			
		template <typename T, typename... Args>
		void SendEventInstantly(Args&&... args);	

		template <typename T, typename... Args>
		void AddEvent(Args&&... args); // reanem? CreateEvemt`?

	private:
		[[nodiscard]] bool IsQueueFull() const;
		void BroadcastEvent(BaseEvent* event);
		 
		std::priority_queue<BaseEvent*, std::vector<BaseEvent*>, EventCompare>	m_events;	 // TODO; Own heap or priority queue?
		// string to event?

		std::vector<EventListener*>												m_listeners;	
	};

#pragma region Method_Definitions 

	// TODO; use memory pool here?

	template <typename T, typename... Args>
	void EventService::SendEventInstantly(Args&&... args)
	{
		T* newEvent = new T(std::forward<Args>(args)...);
		///newEvent->Init();

		BroadcastEvent(newEvent);
		delete newEvent;
	}

	template <typename T, typename... Args>
	void EventService::AddEvent(Args&&... args)
	{
		T* newEvent = new T(std::forward<Args>(args)...);
		//newEvent->Init();

		m_events.push(newEvent);
	}

#pragma endregion Method_Definitions
}