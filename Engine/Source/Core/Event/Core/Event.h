#pragma once
#include "../../../Core/Utility/DataStructures/Linear/Static/MemoryPool/MemoryPool.hpp"

namespace Hi_Engine
{

	enum class ePriority
	{
		Low,
		Moderate,
		High,
		NotSpecified
	};

	class EventListener;

	class BaseEvent
	{
	public:
		virtual ~BaseEvent() {}

		virtual void		Dispatch(EventListener& listener)		  = 0;
		virtual ePriority	GetPriority()						const = 0;
		virtual bool		IsHandled()							const = 0; // used for what?
		virtual void		Reset()									   {}; // not pure virtual?
	};

	template <typename Derived>
	class Event : public BaseEvent
	{
	public:
		Event(ePriority priority);
		~Event();

		void*			operator new (size_t size);
		void			operator delete(void* pointer);

		ePriority		GetPriority()						const override;	// mark final?
		bool			IsHandled()							const override; // mark final?
		void			HandleEvent();

	protected:
		friend struct	EventCompare;

		ePriority		m_priority; // priority should be passed when message is sent. not deafult?!
		bool			m_isHandled;
	};

	/* Comparers */
	struct EventCompare
	{
		bool operator()(const BaseEvent* lhs, const BaseEvent* rhs);
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
		return MemoryPool<Derived>::GetInstance().GetResource();
	}

	template<typename Derived>
	void Event<Derived>::operator delete(void* pointer)
	{
		MemoryPool<Derived>::GetInstance().ReturnResource(static_cast<Derived*>(pointer));
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