#pragma once
#include <cassert>
#include <initializer_list>

//#define DEF_CAP			6
//#define RESIZE_CONST	2

//constexpr int DEF_CAP = 2; // what does this do?
//constexpr int RESIZE_CONST = 2; // what does this do?

// TODO; maybe used memcpy??
// TODO; fix Resize working with smaller size than current...
// TODO: maybe remove m_size (check front- and backindex)

// TEST; Copy/Move assignment and constructors...

namespace Hi_Engine
{
	template <class Type, typename SizeType = unsigned>
	class Queue
	{
	public:
		Queue();
		Queue(const Queue& queue);
		Queue(Queue&& queue)							 noexcept;
		Queue(const std::initializer_list<Type>& list);
		~Queue();

		Queue&	operator=(const Queue& queue);
		Queue&	operator=(Queue&& queue)				 noexcept;

		const Type&		Front()								const;
		Type&			Front();

		void			Enqueue(const Type& value);
		Type			Dequeue();

		SizeType		Capacity()							const;
		SizeType		Size()								const;
		bool			IsEmpty()							const;
		void			Clear();
		void			Resize(const SizeType capacity);

	private:
		bool			IsFull()							const;
		int				NextIndex(int relativeTo)			const;

		Type*			m_data;
		SizeType		m_capacity, m_size;
		int				m_frontIndex, m_backIndex;
		
		int m_numberOfElementsToGrow = 2;
		int m_originalSize = 2; // default capacity
	};

#pragma region Constructor

	template <class Type, typename SizeType>
	Queue<Type, SizeType>::Queue()
		: m_data{ new Type[m_originalSize] }, m_capacity{ m_originalSize }, m_size{ 0 }
	{
		m_frontIndex = m_backIndex = -1;
	}

	template <class Type, typename SizeType>
	Queue<Type, SizeType>::Queue(const Queue& queue)
		: m_data{ new Type[queue.m_capacity] }, m_capacity{ queue.m_capacity }, m_size{ queue.m_size }
	{
		m_frontIndex = queue.m_frontIndex;
		m_backIndex = queue.m_backIndex;

		for (SizeType i = 0; i < queue.m_capacity; ++i)
			m_data[i] = queue.m_data[i];
	}

	template <class Type, typename SizeType>
	Queue<Type, SizeType>::Queue(Queue&& queue) noexcept
		: m_data{ queue.m_data }, m_capacity{ queue.m_capacity }, m_size{ queue.m_size }
	{
		m_frontIndex = queue.m_frontIndex;
		m_backIndex = queue.m_backIndex;

		queue.m_data = nullptr;
		queue.Clear();
	}

	template <class Type, typename SizeType>
	Queue<Type, SizeType>::Queue(const std::initializer_list<Type>& list)
		: m_data{ new Type[list.size()] }, m_capacity{ (SizeType)list.size() }
	{
		m_frontIndex = m_backIndex = -1;

		for (auto& Item : list)
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
	Queue<Type, SizeType>& Queue<Type, SizeType>::operator=(const Queue& queue)
	{
		m_data = new Type[queue.m_capacity];
		m_capacity = queue.m_capacity;
		m_size = queue.m_size;

		m_frontIndex = queue.m_frontIndex;
		m_backIndex = queue.m_backIndex;

		for (SizeType i = 0; i < queue.m_capacity; ++i)
			m_data[i] = queue.m_data[i];

		return *this;
	}

	template <class Type, typename SizeType>
	Queue<Type, SizeType>& Queue<Type, SizeType>::operator=(Queue&& queue) noexcept
	{
		m_data		= queue.m_data;
		m_capacity	= queue.m_capacity;
		m_size		= queue.m_size;

		m_frontIndex = queue.m_frontIndex;
		m_backIndex	 = queue.m_backIndex;

		queue.m_data = nullptr;
		queue.Clear();

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
	void Queue<Type, SizeType>::Enqueue(const Type& value)
	{
		if (IsFull())
		{
			Resize(m_capacity + m_numberOfElementsToGrow);
		}
		else if (IsEmpty())
		{
			++m_frontIndex;
		}

		++m_size;
		m_data[(m_backIndex = NextIndex(m_backIndex))] = value;
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
	void Queue<Type, SizeType>::Resize(const SizeType capacity)
	{
		if (capacity == m_capacity || capacity <= 0)
			return;

		Type* temp = new Type[capacity];

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
		m_capacity = capacity;
	}

	template <class Type, typename SizeType>
	bool Queue<Type, SizeType>::IsFull() const
	{
		return NextIndex(m_backIndex) == m_frontIndex;
	}

	template <class Type, typename SizeType>
	int	Queue<Type, SizeType>::NextIndex(int relativeTo) const
	{
		return (relativeTo + 1) % m_capacity;
	}

#pragma endregion Method_Definitions
}
