#pragma once
#include <cassert>
#include <initializer_list>

#define DEF_CAP			6
#define RESIZE_CONST	2

// TODO; maybe used memcpy??
// TODO; fix Resize working with smaller size than current...
// TODO: maybe remove m_size (check front- and backindex)

// TEST; Copy/Move assignment and constructors...

namespace CommonUtilities
{
	template <class Type, typename SizeType = unsigned>
	class Queue
	{
	public:
		Queue();
		Queue(const Queue& aQueue);
		Queue(Queue&& aQueue)							 noexcept;
		Queue(const std::initializer_list<Type>& aList);
		~Queue();

		Queue&	operator=(const Queue& aQueue);
		Queue&	operator=(Queue&& aQueue)				 noexcept;

		const Type&		Front()								const;
		Type&			Front();

		void			Enqueue(const Type& aValue);
		Type			Dequeue();

		SizeType		Capacity()							const;
		SizeType		Size()								const;
		bool			IsEmpty()							const;
		void			Clear();
		void			Resize(const SizeType aCapacity);

	private:
		bool			IsFull()							const;
		int				NextIndex(int aRelativeTo)			const;

		Type*			m_data;
		SizeType		m_capacity, m_size;
		int				m_frontIndex, m_backIndex;
	};

#pragma region Constructor

	template <class Type, typename SizeType>
	Queue<Type, SizeType>::Queue()
		: m_data{ new Type[DEF_CAP] }, m_capacity{ DEF_CAP }, m_size{ 0 }
	{
		m_frontIndex = m_backIndex = -1;
	}

	template <class Type, typename SizeType>
	Queue<Type, SizeType>::Queue(const Queue& aQueue)
		: m_data{ new Type[aQueue.m_capacity] }, m_capacity{ aQueue.m_capacity }, m_size{ aQueue.m_size }
	{
		m_frontIndex = aQueue.m_frontIndex;
		m_backIndex = aQueue.m_backIndex;

		for (SizeType i = 0; i < aQueue.m_capacity; ++i)
			m_data[i] = aQueue.m_data[i];
	}

	template <class Type, typename SizeType>
	Queue<Type, SizeType>::Queue(Queue&& aQueue) noexcept
		: m_data{ aQueue.m_data }, m_capacity{ aQueue.m_capacity }, m_size{ aQueue.m_size }
	{
		m_frontIndex = aQueue.m_frontIndex;
		m_backIndex = aQueue.m_backIndex;

		aQueue.m_data = nullptr;
		aQueue.Clear();
	}

	template <class Type, typename SizeType>
	Queue<Type, SizeType>::Queue(const std::initializer_list<Type>& aList)
		: m_data{ new Type[aList.size()] }, m_capacity{ (SizeType)aList.size() }
	{
		m_frontIndex = m_backIndex = -1;

		for (auto& Item : aList)
			Enqueue(Item);
	}

	template <class Type, typename SizeType>
	Queue<Type, SizeType>::~Queue()
	{
		delete[] m_data;
	}

#pragma endregion Constructor

#pragma region Operators

	template <class Type, typename SizeType>
	Queue<Type, SizeType>& Queue<Type, SizeType>::operator=(const Queue& aQueue)
	{
		m_data = new Type[aQueue.m_capacity];
		m_capacity = aQueue.m_capacity;
		m_size = aQueue.m_size;

		m_frontIndex = aQueue.m_frontIndex;
		m_backIndex = aQueue.m_backIndex;

		for (SizeType i = 0; i < aQueue.m_capacity; ++i)
			m_data[i] = aQueue.m_data[i];

		return *this;
	}

	template <class Type, typename SizeType>
	Queue<Type, SizeType>& Queue<Type, SizeType>::operator=(Queue&& aQueue) noexcept
	{
		m_data		= aQueue.m_data;
		m_capacity	= aQueue.m_capacity;
		m_size		= aQueue.m_size;

		m_frontIndex = aQueue.m_frontIndex;
		m_backIndex	 = aQueue.m_backIndex;

		aQueue.m_data = nullptr;
		aQueue.Clear();

		return *this;
	}

#pragma endregion Operators

#pragma region Method_Definitions

	template <class Type, typename SizeType>
	const Type& Queue<Type, SizeType>::Front() const
	{
		return Front();
	}

	template <class Type, typename SizeType>
	Type& Queue<Type, SizeType>::Front()
	{
		assert(!IsEmpty() && "Unable to return 'Front' of an empty Queue");
		return m_data[m_frontIndex];
	}

	template <class Type, typename SizeType>
	void Queue<Type, SizeType>::Enqueue(const Type& aValue)
	{
		if (IsFull())
		{
			Resize(m_capacity + RESIZE_CONST);
		}
		else if (IsEmpty())
		{
			++m_frontIndex;
		}

		++m_size;
		m_data[(m_backIndex = NextIndex(m_backIndex))] = aValue;
	}

	template <class Type, typename SizeType>
	Type Queue<Type, SizeType>::Dequeue()
	{
		assert(!IsEmpty() && "Unable to dequeue an empty Queue");

		Type element = m_data[m_frontIndex];

		if (m_frontIndex == m_backIndex)
		{
			Clear();
		}
		else
		{
			m_frontIndex = NextIndex(m_frontIndex);
		}

		--m_size;
		return element;
	}

	template <class Type, typename SizeType>
	SizeType Queue<Type, SizeType>::Capacity() const
	{
		return m_capacity;
	}

	template <class Type, typename SizeType>
	SizeType Queue<Type, SizeType>::Size() const
	{
		return m_size;
	}

	template <class Type, typename SizeType>
	bool Queue<Type, SizeType>::IsEmpty() const
	{
		return m_frontIndex == -1;
	}

	template <class Type, typename SizeType>
	void Queue<Type, SizeType>::Clear()
	{
		m_frontIndex = m_backIndex = -1;
		m_size = 0;
	}

	template <class Type, typename SizeType>
	void Queue<Type, SizeType>::Resize(const SizeType aCapacity)
	{
		if (aCapacity == m_capacity || aCapacity <= 0)
			return;

		Type* temp = new Type[aCapacity];

		if (!IsEmpty())
		{
			int tempIterator = 0;
			int index = m_frontIndex;

			do
			{
				temp[tempIterator++] = m_data[index];
				index = NextIndex(index);
			} while (index != m_frontIndex);

			m_frontIndex = 0;
			m_backIndex = m_capacity - 1;
		}

		delete[] m_data;

		m_data = temp;
		m_capacity = aCapacity;
	}

	template <class Type, typename SizeType>
	bool Queue<Type, SizeType>::IsFull() const
	{
		return NextIndex(m_backIndex) == m_frontIndex;
	}

	template <class Type, typename SizeType>
	int	Queue<Type, SizeType>::NextIndex(int aRelativeTo) const
	{
		return (aRelativeTo + 1) % m_capacity;
	}

#pragma endregion Method_Definitions
}
