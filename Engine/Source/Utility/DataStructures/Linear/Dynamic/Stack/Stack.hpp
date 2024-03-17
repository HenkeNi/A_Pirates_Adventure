#pragma once
#include <cassert>
#include <initializer_list>

#define DEF_CAP			16
#define RESIZE_CONST	2

// TODO: move constructor/assignment AND copy assignment?
// TODO: copy deep function??

namespace CommonUtilities
{
	template <class Type, typename SizeType = unsigned, bool useSafeMode = true>
	class Stack
	{
	public:
		Stack();
		Stack(const Stack& stack);
		Stack(Stack&& stack)								 noexcept;
		Stack(const std::initializer_list<Type>& list);
		~Stack();

		Stack&	operator=(const Stack& stack);
		Stack&	operator=(Stack&& stack)					 noexcept;

		Type&			Top();
		const Type&		Top()									const;

		template		<typename... Args>
		void			Emplace(Args&&... args);
		void			Push(const Type& value);
		Type			Pop();

		SizeType		Size()									const;
		SizeType		Capacity()								const;
		bool			IsEmpty()								const;
		void			Clear();
		void			Resize(const SizeType capacity);

	private:
		Type*			m_data;
		SizeType		m_capacity, m_top;
	};

#pragma region Constructor

	template <class Type, typename SizeType, bool useSafeMode>
	Stack<Type, SizeType, useSafeMode>::Stack()
		: m_data{ new Type[DEF_CAP + RESIZE_CONST] }, m_capacity{ DEF_CAP + RESIZE_CONST }, m_top{ 0 }
	{
	}

	template <class Type, typename SizeType, bool useSafeMode>
	Stack<Type, SizeType, useSafeMode>::Stack(const Stack& stack)
		: m_data{ new Type[stack.m_capacity] }, m_capacity{ stack.m_capacity }, m_top{ stack.m_top }
	{
		assert(&stack != this && "Self assignment detected!");

		if (useSafeMode)
		{
			for (int i = 0; i < stack.Size(); ++i)
				m_data[i] = stack.m_data[i];
		}
		else
		{
			std::memcpy(m_data, stack.m_data, stack.m_top * sizeof(Type));
		}
	}

	template <class Type, typename SizeType, bool useSafeMode>
	Stack<Type, SizeType, useSafeMode>::Stack(const std::initializer_list<Type>& list)
		: m_data{ new Type[list.size() + RESIZE_CONST] }, m_capacity{ (SizeType)list.size() + RESIZE_CONST }
	{
		if (useSafeMode)
		{
			for (int i = 0; i < list.size(); ++i)
				m_data[m_top++] = *(list.begin() + i);
		}
		else
		{
			m_top = list.size();
			std::memcpy(m_data, list.begin(), list.size() * sizeof(Type));
		}
	}

	template <class Type, typename SizeType, bool useSafeMode>
	Stack<Type, SizeType, useSafeMode>::Stack(Stack&& stack) noexcept
		: m_data{ stack.m_data }, m_capacity{ stack.m_capacity }, m_top{ stack.m_top }
	{
		stack.m_data = nullptr;
		stack.Clear();
	}

	template <class Type, typename SizeType, bool useSafeMode>
	Stack<Type, SizeType, useSafeMode>::~Stack()
	{
		delete[] m_data;
	}

#pragma endregion Constructor

#pragma region Operators

	template <class Type, typename SizeType, bool useSafeMode>
	Stack<Type, SizeType, useSafeMode>& Stack<Type, SizeType, useSafeMode>::operator=(const Stack& stack)
	{
		m_data = new Type[stack.m_capacity];
		m_capacity = stack.m_capacity;
		m_top = stack.m_top;

		if (useSafeMode)
		{
			for (int i = 0; i < stack.Size(); ++i)
				m_data[i] = stack.m_data[i];
		}
		else
		{
			std::memcpy(m_data, stack.m_data, stack.m_top * sizeof(Type));
		}

		return *this;
	}

	template <class Type, typename SizeType, bool useSafeMode>
	Stack<Type, SizeType, useSafeMode>& Stack<Type, SizeType, useSafeMode>::operator=(Stack&& stack) noexcept
	{
		m_data = stack.m_data;
		m_capacity = stack.m_capacity;
		m_top = stack.m_top;

		stack.m_data = nullptr;
		stack.Clear();

		return *this;
	}

#pragma endregion Operators

#pragma region Method_Definitions

	template <class Type, typename SizeType, bool useSafeMode>
	Type& Stack<Type, SizeType, useSafeMode>::Top()
	{
		assert(!IsEmpty() && "Unable get Top an empty stack");

		return m_data[m_top - 1];
	}

	template <class Type, typename SizeType, bool useSafeMode>
	const Type& Stack<Type, SizeType, useSafeMode>::Top() const
	{
		assert(!IsEmpty() && "Unable get Top an empty stack");

		return m_data[m_top - 1];
	}

	template <class Type, typename SizeType, bool useSafeMode>
	template <typename... Args>
	void Stack<Type, SizeType, useSafeMode>::Emplace(Args&&... args)
	{
		if (m_top == m_capacity)
			Resize(m_capacity + RESIZE_CONST);

		m_data[m_top++] = Type{ std::forward<Args>(args)... };
	}

	template <class Type, typename SizeType, bool useSafeMode>
	void Stack<Type, SizeType, useSafeMode>::Push(const Type& value)
	{
		if (m_top == m_capacity)
			Resize(m_capacity + RESIZE_CONST);

		m_data[m_top++] = value;
	}

	template <class Type, typename SizeType, bool useSafeMode>
	Type Stack<Type, SizeType, useSafeMode>::Pop()
	{
		assert(!IsEmpty() && "Unable Pop an empty stack");

		return m_data[--m_top];
	}

	template <class Type, typename SizeType, bool useSafeMode>
	SizeType Stack<Type, SizeType, useSafeMode>::Size() const
	{
		return m_top;
	}

	template <class Type, typename SizeType, bool useSafeMode>
	SizeType Stack<Type, SizeType, useSafeMode>::Capacity() const
	{
		return m_capacity;
	}

	template <class Type, typename SizeType, bool useSafeMode>
	bool Stack<Type, SizeType, useSafeMode>::IsEmpty()	const
	{
		return m_top == 0;
	}

	template <class Type, typename SizeType, bool useSafeMode>
	void Stack<Type, SizeType, useSafeMode>::Clear()
	{
		m_top = 0;
	}

	template <class Type, typename SizeType, bool useSafeMode>
	void Stack<Type, SizeType, useSafeMode>::Resize(const SizeType capacity)
	{
		if (capacity == m_capacity || capacity <= 0)
			return;

		Type* temp = new Type[capacity];
		SizeType elementsToCopy = capacity > m_capacity ? m_capacity : capacity;

		if (!IsEmpty())
		{
			if (useSafeMode)
			{
				for (int i = 0; i < elementsToCopy; ++i)
					temp[i] = m_data[i];
			}
			else
				std::memcpy(temp, m_data, elementsToCopy * sizeof(Type));
		}

		delete[] m_data;

		m_data = temp;
		m_top = capacity < m_capacity ? capacity : m_top;
		m_capacity = capacity;
	}

#pragma endregion Method_Definitions
}
