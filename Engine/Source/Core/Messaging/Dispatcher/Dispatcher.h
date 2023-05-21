#pragma once
#include "Data/Enumerations.h"
#include "Data/Structs.h"
#include "../../../Utility/DataStructures/Linear/Static/MemoryPool/MemoryPool.hpp"
#include <queue>


// TODO: replace array with Binary Search Tree Set or AVL or SPlay Tree? or map
// Todo: rename EventSystem?? or MessageSystem??
// TODO; check if sorting after importance works?

namespace Hi_Engine
{
	namespace CU = CommonUtilities;

	class Event;
	class EventListener;

	class Dispatcher
	{
	public:
		Dispatcher(const Dispatcher&)				= delete;
		Dispatcher& operator=(const Dispatcher&)	= delete;

		static Dispatcher& GetInstance();

		void Subscribe(EventListener* aSubscriber);
		void Unsubscribe(EventListener* aSubscriber);

		void DispatchEvents();								// Rename Broadcast or BroadcastEvents?
			
		template <typename T, typename... Args>
		void SendEventInstantly(Args&&... args);			

		template <typename T, typename... Args>
		void AddEvent(Args&&... args);

		template <typename T>
		void AddEvent();

	private:
		Dispatcher() = default;

		bool IsQueueFull() const;
		void BroadcastEvent(Event* anEvent);
		 
		std::priority_queue<Event*, std::vector<Event*>, EventCompare>	m_events;				// TODO; Own heap or priority queue?
		std::vector<EventListener*>										m_listeners;	
	};

#pragma region Method_Definitions

	template <typename T, typename... Args>
	void Dispatcher::SendEventInstantly(Args&&... args)
	{
		T* newEvent = CU::MemoryPool<T>::GetInstance().GetResource();
		newEvent->Init(std::forward<Args>(args)...);

		BroadcastEvent(newEvent);

		CU::MemoryPool<T>::GetInstance().ReturnResource(newEvent); // return resource again...
	}

	template <typename T, typename... Args>
	void Dispatcher::AddEvent(Args&&... args)
	{
		T* newEvent = CU::MemoryPool<T>::GetInstance().GetResource();
		newEvent->Init(std::forward<Args>(args)...);						// Override placement new instead??

		m_events.push(newEvent);
	}

	template <typename T>
	void Dispatcher::AddEvent()
	{
		T* newEvent = CU::MemoryPool<T>::GetInstance().GetResource();
		m_events.push(newEvent);
	}

#pragma endregion Method_Definitions
}