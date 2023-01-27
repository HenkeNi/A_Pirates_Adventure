#pragma once
#include "Data/Enumerations.h"
#include "DataStructures/Linear/Static/MemoryPool/MemoryPool.hpp"


namespace Hi_Engine
{
	namespace CU = CommonUtilities;

	class Event;
	class EventListener;

	// Todo: rename EventSystem??
	class Dispatcher
	{
	public:
		Dispatcher(const Dispatcher&) = delete;
		Dispatcher& operator=(const Dispatcher&) = delete;

		static Dispatcher& GetInstance();

		void Subscribe(EventListener* aSubscriber);
		void Unsubscribe(EventListener* aSubscriber);

		template <typename T>
		void AddEvent();

		template <typename T, typename... Args>
		void AddEvent(Args&&... args);

		void SendEvent(Event* anEvent);

	private:
		Dispatcher() = default;

		bool IsQueueFull() const;


		// TODO: replace array with Binary Search Tree Set or AVL or SPlay Tree? or map
		std::vector<EventListener*> m_listeners;

		//std::vector<Event*> m_events; 

		// TODO: if nothing works have an array with preallocated memory?? or map?

		//CU::MemoryPool<Event*> m_eventPool;
	};


#pragma region Method_Definitions

	// TODO: Sort by importance...


// Publish function()??
// insert//add event..

	template <typename T>
	void Dispatcher::AddEvent()
	{
		//T* newEvent = m_eventPool.GetResource();

		//T* tEvent = new T;

	}


	template <typename T, typename... Args>
	void Dispatcher::AddEvent(Args&&... args)
	{
		// In init??

		//T* tEvent = new T;
	}

#pragma endregion Method_Definitions
}