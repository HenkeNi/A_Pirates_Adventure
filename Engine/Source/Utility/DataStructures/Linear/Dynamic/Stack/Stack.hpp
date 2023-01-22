#pragma once

namespace CommonUtilities
{
	template <class Type, bool isStatic = true, typename SizeType = unsigned>
	class Stack
	{
	public:
		Stack(const SizeType aCapacity = 16);
		~Stack();

		SizeType	Size()		const;
		SizeType	Capacity()	const;
		const Type&	Top()		const;
		Type&		Top();

		bool		IsEmpty()	const;
		bool		IsFull()	const;

		void		Push(const Type& aValue);
		Type		Pop();
		void		Resize(const SizeType aCapacity);
		void		Clear();

	private:
		Type*		m_data;
		SizeType	m_capacity;
		int			m_top;
	};

#pragma region CONSTRUCTOR

	template <class Type, bool isStatic, typename SizeType>
	Stack<Type, isStatic, SizeType>::Stack(const SizeType aCapacity)
		: m_data{ new Type[aCapacity] }, m_capacity{ aCapacity }, m_top{ 0 }
	{
	}

	template <class Type, bool isStatic, typename SizeType>
	Stack<Type, isStatic, SizeType>::~Stack()
	{
		delete[] m_data;
	}

#pragma endregion CONSTRUCTOR

#pragma region METHOD_DEFINITIONS

	template <class Type, bool isStatic, typename SizeType>
	SizeType Stack<Type, isStatic, SizeType>::Size()		const
	{
		return m_top;
	}

	template <class Type, bool isStatic, typename SizeType>
	SizeType Stack<Type, isStatic, SizeType>::Capacity()	const
	{
		return m_capacity;
	}

	template <class Type, bool isStatic, typename SizeType>
	const Type& Stack<Type, isStatic, SizeType>::Top()		const
	{
		assert(!IsEmpty() && "Unable to get top element of an empty stack!");
		return m_data[m_top - 1];
	}

	template <class Type, bool isStatic, typename SizeType>
	Type& Stack<Type, isStatic, SizeType>::Top()
	{
		assert(!IsEmpty() && "Unable to get top element of an empty stack!");
		return m_data[m_top - 1];
	}

	template <class Type, bool isStatic, typename SizeType>
	bool Stack<Type, isStatic, SizeType>::IsEmpty()			const
	{
		return m_top == 0;
	}

	template <class Type, bool isStatic, typename SizeType>
	bool Stack<Type, isStatic, SizeType>::IsFull()			const
	{
		return m_top == m_capacity;
	}

	template <class Type, bool isStatic, typename SizeType>
	void Stack<Type, isStatic, SizeType>::Push(const Type& aValue)
	{
		if (IsFull())
		{
			if (isStatic)
				assert(false && "Stack is full");
			else
				Resize(m_capacity * 2);
		}

		m_data[m_top++] = aValue;
	}

	template <class Type, bool isStatic, typename SizeType>
	Type Stack<Type, isStatic, SizeType>::Pop()
	{
		assert(!IsEmpty() && "Unable to pop element of an empty stack!");
		return m_data[--m_top];
	}

	template <class Type, bool isStatic, typename SizeType>
	void Stack<Type, isStatic, SizeType>::Resize(const SizeType aCapacity)
	{
		assert(!isStatic && "This Stack is a static data structure!");

		auto* temp = new Type[aCapacity];
		for (int i = 0; i < m_top; ++i)
		{
			temp[i] = m_data[i];
		}

		delete[] m_data;
		m_data = temp;

		m_capacity = aCapacity;
	}

	template <class Type, bool isStatic, typename SizeType>
	void Stack<Type, isStatic, SizeType>::Clear()
	{
		m_top = 0;
	}

#pragma endregion METHOD_DEFINITIONS
}