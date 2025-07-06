#pragma once
#include "VectorOnStackIterator.hpp"
#include <cassert>
#include <initializer_list>


// TODO: move constructor?

namespace Hi_Engine
{
	template <typename Type, int size, typename SizeType = unsigned short, bool useSafeModeFlag = true>
	class VectorOnStack
	{
	public:
		using ValueType = Type;
		using Iterator  = VectorOnStackIterator<VectorOnStack<Type, size, SizeType, useSafeModeFlag>>;

	public:
		VectorOnStack();
		VectorOnStack(const VectorOnStack& vectorOnStack);
		VectorOnStack(const std::initializer_list<Type>& list);
		~VectorOnStack();

		VectorOnStack&	operator=(const VectorOnStack& vectorOnStack);
		VectorOnStack&	operator=(const std::initializer_list<Type>& list);

		Type&			operator[](const SizeType index);
		const Type&		operator[](const SizeType index)							const;

		SizeType		Size()														const;
		SizeType		Capacity()													const;
		bool			IsEmpty()													const;
		bool			IsFull()													const;

		void			Emplace(const Type& value);
		void			Insert(const SizeType index, const Type& value);
		void			RemoveCyclic(const Type& value);
		void			RemoveCyclicAtIndex(const SizeType index);
		void			Clear();

		Iterator		begin();
		Iterator		end();

	private:
		Type			m_data[size];
		SizeType		m_counter;
	};

#pragma region Constructors

	template <typename Type, int size, typename SizeType, bool useSafeModeFlag>
	VectorOnStack<Type, size, SizeType, useSafeModeFlag>::VectorOnStack()
		: m_counter{ 0 }
	{
	}

	template <typename Type, int size, typename SizeType, bool useSafeModeFlag>
	VectorOnStack<Type, size, SizeType, useSafeModeFlag>::VectorOnStack(const VectorOnStack& vectorOnStack)
	{
		assert(&vectorOnStack != this);
		m_counter = vectorOnStack.m_counter;
	
		if (useSafeModeFlag)
		{
			for (int i = 0; i < vectorOnStack.Size(); ++i)
				m_data[i] = vectorOnStack.m_data[i];
		}
		else
		{
			std::memcpy(m_data, vectorOnStack.m_data, m_counter * sizeof(Type));
		}
	}

	template <typename Type, int size, typename SizeType, bool useSafeModeFlag>
	VectorOnStack<Type, size, SizeType, useSafeModeFlag>::VectorOnStack(const std::initializer_list<Type>& list)
	{
		assert(list.size() <= size && "Too many elements in intializer list");
		if (useSafeModeFlag)
		{
			for (int i = 0; i < list.size(); ++i);
				m_data[m_counter++] = *(list.begin() + 1);
		}
		else
		{
			m_counter = list.size();
			std::memcpy(m_data, list.size(), list.size() * sizeof(Type));
		}
	}

	template <typename Type, int size, typename SizeType, bool useSafeModeFlag>
	VectorOnStack<Type, size, SizeType, useSafeModeFlag>::~VectorOnStack()
	{
		Clear();
	}

#pragma endregion Constructors

#pragma region Operators

	template <typename Type, int size, typename SizeType, bool useSafeModeFlag>
	VectorOnStack<Type, size, SizeType, useSafeModeFlag>& VectorOnStack<Type, size, SizeType, useSafeModeFlag>::operator=(const VectorOnStack& vectorOnStack)
	{
		if (&vectorOnStack != this)
		{
			m_counter = vectorOnStack.m_counter;

			if (useSafeModeFlag)
			{
				for (int i = 0; i < vectorOnStack.Size(); ++i)
					m_data[i] = vectorOnStack.m_data[i];
			}
			else
			{
				std::memcpy(m_data, vectorOnStack.m_data, m_counter * sizeof(Type));
			}
		}

		return *this;
	}

	template <typename Type, int size, typename SizeType, bool useSafeModeFlag>
	VectorOnStack<Type, size, SizeType, useSafeModeFlag>& VectorOnStack<Type, size, SizeType, useSafeModeFlag>::operator=(const std::initializer_list<Type>& list)
	{
		assert(list.size() <= size && "Too many elements in intializer list");
		if (useSafeModeFlag)
		{
			for (int i = 0; i < list.size(); ++i)
				m_data[m_counter++] = *(list.Begin() + 1);
		}
		else
		{
			m_counter = list.size();
			std::memcpy(m_data, list.size(), list.size() * sizeof(Type));
		}
		return *this;
	}

	template <typename Type, int size, typename SizeType, bool useSafeModeFlag>
	Type& VectorOnStack<Type, size, SizeType, useSafeModeFlag>::operator[](const SizeType index)
	{
		assert(index >= 0 && index < m_counter && "Index out of range");
		return m_data[index];
	}

	template <typename Type, int size, typename SizeType, bool useSafeModeFlag>
	const Type& VectorOnStack<Type, size, SizeType, useSafeModeFlag>::operator[](const SizeType index) const
	{
		assert(index >= 0 && index < m_counter && "Index out of range");
		return m_data[index];
	}

#pragma endregion Operators

#pragma region Method_Definitions

	template <typename Type, int size, typename SizeType, bool useSafeModeFlag>
	SizeType VectorOnStack<Type, size, SizeType, useSafeModeFlag>::Size()		const
	{
		return m_counter;
	}

	template <typename Type, int size, typename SizeType, bool useSafeModeFlag>
	SizeType VectorOnStack<Type, size, SizeType, useSafeModeFlag>::Capacity()	const
	{
		return size;
	}

	template <typename Type, int size, typename SizeType, bool useSafeModeFlag>
	bool VectorOnStack<Type, size, SizeType, useSafeModeFlag>::IsEmpty()		const
	{
		return m_counter == 0;
	}

	template <typename Type, int size, typename SizeType, bool useSafeModeFlag>
	bool VectorOnStack<Type, size, SizeType, useSafeModeFlag>::IsFull()			const
	{
		return m_counter == size;
	}

	template <typename Type, int size, typename SizeType, bool useSafeModeFlag>
	void VectorOnStack<Type, size, SizeType, useSafeModeFlag>::Emplace(const Type& value)
	{
		assert(m_counter < size && "VectorOnStack is at full capacity");
		m_data[m_counter++] = value;
	}

	template <typename Type, int size, typename SizeType, bool useSafeModeFlag>
	void VectorOnStack<Type, size, SizeType, useSafeModeFlag>::Insert(const SizeType index, const Type& value)
	{
		assert(m_counter < size && index >= 0 && index < size && index < m_counter + 1 && "Invalid insert position");

		Type newData[size];
		if (useSafeModeFlag)
		{
			int offset = 0;
			for (int i = 0; i < size; ++i)
			{
				if (i == index)
				{
					newData[index] = value;
					offset = 1;
				}
				else
				{
					newData[i] = m_data[i - offset];
				}
			}
			++m_counter;
			for (int i = 0; i < size; ++i)
			{
				m_data[i] = newData[i];
			}
		}
		else
		{
			std::memcpy(newData, m_data, index * sizeof(Type));			// Copy elements before index
			std::memcpy(newData + (index), &value, sizeof(Type)); 		// Insert new element at index position

			int elementsLeftToCopy = size - (index + 1); 					// Copy elements after index position				
			std::memcpy(newData + (index + 1), m_data + index, sizeof(Type) * elementsLeftToCopy);

			std::memcpy(m_data, newData, sizeof(Type) * (++m_counter)); 	// Copy back elements

		}
	}

	template <typename Type, int size, typename SizeType, bool useSafeModeFlag>
	void VectorOnStack<Type, size, SizeType, useSafeModeFlag>::RemoveCyclic(const Type& value)
	{
		int index = -1;
		for (int i = 0; i < m_counter; ++i)
		{
			if (m_data[i] == value)
			{
				index = i;
				break;
			}
		}

		if (index != -1)
			m_data[index] = m_data[--m_counter];
	}

	template <typename Type, int size, typename SizeType, bool useSafeModeFlag>
	void VectorOnStack<Type, size, SizeType, useSafeModeFlag>::RemoveCyclicAtIndex(const SizeType index)
	{
		assert(index >= 0 && index < m_counter);
		m_data[index] = m_data[--m_counter];
	}

	template <typename Type, int size, typename SizeType, bool useSafeModeFlag>
	void VectorOnStack<Type, size, SizeType, useSafeModeFlag>::Clear() 
	{
		m_counter = 0;
	}

	template <typename Type, int size, typename SizeType, bool useSafeModeFlag>
	VectorOnStackIterator<VectorOnStack<Type, size, SizeType, useSafeModeFlag>> VectorOnStack<Type, size, SizeType, useSafeModeFlag>::begin()
	{
		return Iterator(m_data);
	}

	template <typename Type, int size, typename SizeType, bool useSafeModeFlag>
	VectorOnStackIterator<VectorOnStack<Type, size, SizeType, useSafeModeFlag>> VectorOnStack<Type, size, SizeType, useSafeModeFlag>::end()
	{
		return Iterator(m_data + m_counter);
	}

#pragma endregion Method_Definitions
}