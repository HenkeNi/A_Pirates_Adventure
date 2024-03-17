#pragma once


namespace CommonUtilities
{
	template <class VectorOnStack>
	class VectorOnStackIterator
	{
	public:
		using ValueType = typename VectorOnStack::ValueType;

	public:
		VectorOnStackIterator(ValueType* pointer);

		VectorOnStackIterator&	operator++();
		VectorOnStackIterator&	operator++(int);
		VectorOnStackIterator&	operator--();
		VectorOnStackIterator&	operator--(int);

		ValueType&				operator[](int index);
		ValueType&				operator*();
		ValueType*				operator->();

		bool					operator==(const VectorOnStackIterator& other) const;
		bool					operator!=(const VectorOnStackIterator& other) const;

	private:
		ValueType*	m_ptr;
	};

#pragma region		Method_Definitions

	template <class VectorOnStack>
	VectorOnStackIterator<VectorOnStack>::VectorOnStackIterator(ValueType* pointer)
		: m_ptr{ pointer }
	{
	}

	template <class VectorOnStack>
	VectorOnStackIterator<VectorOnStack>& VectorOnStackIterator<VectorOnStack>::operator++()
	{
		m_ptr++;
		return *this;
	}

	template <class VectorOnStack>
	VectorOnStackIterator<VectorOnStack>& VectorOnStackIterator<VectorOnStack>::operator++(int)
	{
		VectorOnStackIterator iterator = *this;
		++(*this);

		return iterator;
	}

	template <class VectorOnStack>
	VectorOnStackIterator<VectorOnStack>& VectorOnStackIterator<VectorOnStack>::operator--()
	{
		m_ptr--;
		return *this;
	}

	template <class VectorOnStack>
	VectorOnStackIterator<VectorOnStack>& VectorOnStackIterator<VectorOnStack>::operator--(int)
	{
		VectorOnStackIterator iterator = *this;
		--(*this);

		return iterator;
	}

	template <class VectorOnStack>
	typename VectorOnStack::ValueType& VectorOnStackIterator<VectorOnStack>::operator[](int index)
	{
		return *(m_ptr[index]);
	}

	template <class VectorOnStack>
	typename VectorOnStack::ValueType& VectorOnStackIterator<VectorOnStack>::operator*()
	{
		return *m_ptr;
	}

	template <class VectorOnStack>
	typename VectorOnStack::ValueType* VectorOnStackIterator<VectorOnStack>::operator->()
	{
		return m_ptr;
	}

	template <class VectorOnStack>
	bool VectorOnStackIterator<VectorOnStack>::operator==(const VectorOnStackIterator& other) const
	{
		return m_ptr == other.m_ptr;
	}

	template <class VectorOnStack>
	bool VectorOnStackIterator<VectorOnStack>::operator!=(const VectorOnStackIterator& other) const
	{
		return !(*this == other);
	}

#pragma endregion	Method_Definitions
}