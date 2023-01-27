#pragma once
#include "../../../Iterators/VectorOnStackIterator.hpp"
#include <cassert>
#include <initializer_list>


namespace CommonUtilities
{
	template <typename Type, int size, typename SizeType = unsigned short, bool useSafeModeFlag = true>
	class VectorOnStack
	{
	public:
		using ValueType = Type;
		using Iterator  = VectorOnStackIterator<VectorOnStack<Type, size, SizeType, useSafeModeFlag>>;

	public:
		VectorOnStack();
		VectorOnStack(const VectorOnStack& aVectorOnStack);
		VectorOnStack(const std::initializer_list<Type>& aList);
		~VectorOnStack();

		VectorOnStack&	operator=(const VectorOnStack& aVectorOnStack);
		VectorOnStack&	operator=(const std::initializer_list<Type>& aList);

		Type&			operator[](const SizeType anIndex);
		const Type&		operator[](const SizeType anIndex)							const;

		SizeType		Size()														const;
		SizeType		Capacity()													const;
		bool			IsEmpty()													const;
		bool			IsFull()													const;

		void			Add(const Type& aValue);
		void			Insert(const SizeType anIndex, const Type& aValue);
		void			RemoveCyclic(const Type& aValue);
		void			RemoveCyclicAtIndex(const SizeType anIndex);
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
	VectorOnStack<Type, size, SizeType, useSafeModeFlag>::VectorOnStack(const VectorOnStack& aVectorOnStack)
	{
		assert(&aVectorOnStack != this);
		m_counter = aVectorOnStack.m_counter;
	
		if (useSafeModeFlag)
		{
			for (int i = 0; i < aVectorOnStack.Size(); ++i)
				m_data[i] = aVectorOnStack.m_data[i];
		}
		else
		{
			std::memcpy(m_data, aVectorOnStack.m_data, m_counter * sizeof(Type));
		}
	}

	template <typename Type, int size, typename SizeType, bool useSafeModeFlag>
	VectorOnStack<Type, size, SizeType, useSafeModeFlag>::VectorOnStack(const std::initializer_list<Type>& aList)
	{
		assert(aList.size() <= size && "Too many elements in intializer list");
		if (useSafeModeFlag)
		{
			for (int i = 0; i < aList.size(); ++i);
				m_data[m_counter++] = *(aList.begin() + 1);
		}
		else
		{
			m_counter = aList.size();
			std::memcpy(m_data, aList.size(), aList.size() * sizeof(Type));
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
	VectorOnStack<Type, size, SizeType, useSafeModeFlag>& VectorOnStack<Type, size, SizeType, useSafeModeFlag>::operator=(const VectorOnStack& aVectorOnStack)
	{
		if (&aVectorOnStack != this)
		{
			m_counter = aVectorOnStack.m_counter;

			if (useSafeModeFlag)
			{
				for (int i = 0; i < aVectorOnStack.Size(); ++i)
					m_data[i] = aVectorOnStack.m_data[i];
			}
			else
			{
				std::memcpy(m_data, aVectorOnStack.m_data, m_counter * sizeof(Type));
			}
		}

		return *this;
	}

	template <typename Type, int size, typename SizeType, bool useSafeModeFlag>
	VectorOnStack<Type, size, SizeType, useSafeModeFlag>& VectorOnStack<Type, size, SizeType, useSafeModeFlag>::operator=(const std::initializer_list<Type>& aList)
	{
		assert(aList.size() <= size && "Too many elements in intializer list");
		if (useSafeModeFlag)
		{
			for (int i = 0; i < aList.size(); ++i)
				m_data[m_counter++] = *(aList.Begin() + 1);
		}
		else
		{
			m_counter = aList.size();
			std::memcpy(m_data, aList.size(), aList.size() * sizeof(Type));
		}
		return *this;
	}

	template <typename Type, int size, typename SizeType, bool useSafeModeFlag>
	Type& VectorOnStack<Type, size, SizeType, useSafeModeFlag>::operator[](const SizeType anIndex)
	{
		assert(anIndex >= 0 && anIndex < m_counter && "Index out of range");
		return m_data[anIndex];
	}

	template <typename Type, int size, typename SizeType, bool useSafeModeFlag>
	const Type& VectorOnStack<Type, size, SizeType, useSafeModeFlag>::operator[](const SizeType anIndex) const
	{
		assert(anIndex >= 0 && anIndex < m_counter && "Index out of range");
		return m_data[anIndex];
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
	void VectorOnStack<Type, size, SizeType, useSafeModeFlag>::Add(const Type& aValue)
	{
		assert(m_counter < size && "VectorOnStack is at full capacity");
		m_data[m_counter++] = aValue;
	}

	template <typename Type, int size, typename SizeType, bool useSafeModeFlag>
	void VectorOnStack<Type, size, SizeType, useSafeModeFlag>::Insert(const SizeType anIndex, const Type& aValue)
	{
		assert(m_counter < size && anIndex >= 0 && anIndex < size && anIndex < m_counter + 1 && "Invalid insert position");

		Type newData[size];
		if (useSafeModeFlag)
		{
			int offset = 0;
			for (int i = 0; i < size; ++i)
			{
				if (i == anIndex)
				{
					newData[anIndex] = aValue;
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
			std::memcpy(newData, m_data, anIndex * sizeof(Type));			// Copy elements before index
			std::memcpy(newData + (anIndex), &aValue, sizeof(Type)); 		// Insert new element at index position

			int elementsLeftToCopy = size - (anIndex + 1); 					// Copy elements after index position				
			std::memcpy(newData + (anIndex + 1), m_data + anIndex, sizeof(Type) * elementsLeftToCopy);

			std::memcpy(m_data, newData, sizeof(Type) * (++m_counter)); 	// Copy back elements

		}
	}

	template <typename Type, int size, typename SizeType, bool useSafeModeFlag>
	void VectorOnStack<Type, size, SizeType, useSafeModeFlag>::RemoveCyclic(const Type& aValue)
	{
		int index = -1;
		for (int i = 0; i < m_counter; ++i)
		{
			if (m_data[i] == aValue)
			{
				index = i;
				break;
			}
		}

		if (index != -1)
			m_data[index] = m_data[--m_counter];
	}

	template <typename Type, int size, typename SizeType, bool useSafeModeFlag>
	void VectorOnStack<Type, size, SizeType, useSafeModeFlag>::RemoveCyclicAtIndex(const SizeType anIndex)
	{
		assert(anIndex >= 0 && anIndex < m_counter);
		m_data[anIndex] = m_data[--m_counter];
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