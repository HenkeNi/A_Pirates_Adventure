#pragma once
#include "../Data/Enumerations.h"
#include "../Utility/DataStructures/Linear/Static/MemoryPool/MemoryPool.hpp"

namespace Hi_Engine
{
	class EventListener;
	class BaseEvent
	{
	public:
		virtual ~BaseEvent() {}

		virtual void		Dispatch(EventListener& listener)		  = 0;
		virtual ePriority	GetPriority()						const = 0;
		virtual bool		IsHandled()							const = 0; // used for what?
		virtual void		Reset()									  = 0; // not pure virtual?
	};

	template <typename Derived>
	class Event : public BaseEvent
	{
	public:
		Event(ePriority priority = ePriority::Moderate);
		~Event();

		void*			operator new (size_t size);
		void			operator delete(void* pointer);

		ePriority		GetPriority()						const override;
		bool			IsHandled()							const override;
		void			HandleEvent();

	protected:
		friend struct	EventCompare;

		ePriority		m_priority;
		bool			m_isHandled;
	};

#pragma region Constructors

	template <typename Derived>
	Event<Derived>::Event(ePriority priority)
		: m_priority{ priority }, m_isHandled{ false }
	{
	}
	
	template <typename Derived>
	Event<Derived>::~Event()
	{
	}

#pragma endregion Constructors

#pragma region Method_Definitions

	template<typename Derived>
	void* Event<Derived>::operator new(size_t size)
	{
		return CommonUtilities::MemoryPool<Derived>::GetInstance().GetResource();
	}

	template<typename Derived>
	void Event<Derived>::operator delete(void* pointer)
	{
		CommonUtilities::MemoryPool<Derived>::GetInstance().ReturnResource(static_cast<Derived*>(pointer));
	}

	template<typename Derived>
	ePriority Event<Derived>::GetPriority() const
	{
		return m_priority;
	}

	template<typename Derived>
	bool Event<Derived>::IsHandled() const
	{
		return m_isHandled;
	}

	template<typename Derived>
	void Event<Derived>::HandleEvent()
	{
		m_isHandled = true;
	}

#pragma endregion Method_Definitions
}