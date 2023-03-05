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
		Stack(const Stack& aStack);
		Stack(Stack&& aStack)								 noexcept;
		Stack(const std::initializer_list<Type>& aList);
		~Stack();

		Stack&	operator=(const Stack& aStack);
		Stack&	operator=(Stack&& aStack)					 noexcept;

		Type&			Top();
		const Type&		Top()									const;

		template		<typename... Args>
		void			Emplace(Args&&... args);
		void			Push(const Type& aValue);
		Type			Pop();

		SizeType		Size()									const;
		SizeType		Capacity()								const;
		bool			IsEmpty()								const;
		void			Clear();
		void			Resize(const SizeType aCapacity);

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
	Stack<Type, SizeType, useSafeMode>::Stack(const Stack& aStack)
		: m_data{ new Type[aStack.m_capacity] }, m_capacity{ aStack.m_capacity }, m_top{ aStack.m_top }
	{
		assert(&aStack != this && "Self assignment detected!");

		if (useSafeMode)
		{
			for (int i = 0; i < aStack.Size(); ++i)
				m_data[i] = aStack.m_data[i];
		}
		else
		{
			std::memcpy(m_data, aStack.m_data, aStack.m_top * sizeof(Type));
		}
	}

	template <class Type, typename SizeType, bool useSafeMode>
	Stack<Type, SizeType, useSafeMode>::Stack(const std::initializer_list<Type>& aList)
		: m_data{ new Type[aList.size() + RESIZE_CONST] }, m_capacity{ (SizeType)aList.size() + RESIZE_CONST }
	{
		if (useSafeMode)
		{
			for (int i = 0; i < aList.size(); ++i)
				m_data[m_top++] = *(aList.begin() + i);
		}
		else
		{
			m_top = aList.size();
			std::memcpy(m_data, aList.begin(), aList.size() * sizeof(Type));
		}
	}

	template <class Type, typename SizeType, bool useSafeMode>
	Stack<Type, SizeType, useSafeMode>::Stack(Stack&& aStack) noexcept
		: m_data{ aStack.m_data }, m_capacity{ aStack.m_capacity }, m_top{ aStack.m_top }
	{
		aStack.m_data = nullptr;
		aStack.Clear();
	}

	template <class Type, typename SizeType, bool useSafeMode>
	Stack<Type, SizeType, useSafeMode>::~Stack()
	{
		delete[] m_data;
	}

#pragma endregion Constructor

#pragma region Operators

	template <class Type, typename SizeType, bool useSafeMode>
	Stack<Type, SizeType, useSafeMode>& Stack<Type, SizeType, useSafeMode>::operator=(const Stack& aStack)
	{
		m_data = new Type[aStack.m_capacity];
		m_capacity = aStack.m_capacity;
		m_top = aStack.m_top;

		if (useSafeMode)
		{
			for (int i = 0; i < aStack.Size(); ++i)
				m_data[i] = aStack.m_data[i];
		}
		else
		{
			std::memcpy(m_data, aStack.m_data, aStack.m_top * sizeof(Type));
		}

		return *this;
	}

	template <class Type, typename SizeType, bool useSafeMode>
	Stack<Type, SizeType, useSafeMode>& Stack<Type, SizeType, useSafeMode>::operator=(Stack&& aStack) noexcept
	{
		m_data = aStack.m_data;
		m_capacity = aStack.m_capacity;
		m_top = aStack.m_top;

		aStack.m_data = nullptr;
		aStack.Clear();

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
	void Stack<Type, SizeType, useSafeMode>::Push(const Type& aValue)
	{
		if (m_top == m_capacity)
			Resize(m_capacity + RESIZE_CONST);

		m_data[m_top++] = aValue;
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
	void Stack<Type, SizeType, useSafeMode>::Resize(const SizeType aCapacity)
	{
		if (aCapacity == m_capacity || aCapacity <= 0)
			return;

		Type* temp = new Type[aCapacity];
		SizeType elementsToCopy = aCapacity > m_capacity ? m_capacity : aCapacity;

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
		m_top = aCapacity < m_capacity ? aCapacity : m_top;
		m_capacity = aCapacity;
	}

#pragma endregion Method_Definitions
}
