#pragma once


namespace CommonUtilities
{
	template <class VectorOnStack>
	class VectorOnStackIterator
	{
	public:
		using ValueType = typename VectorOnStack::ValueType;

	public:
		VectorOnStackIterator(ValueType* aPtr);

		VectorOnStackIterator&	operator++();
		VectorOnStackIterator&	operator++(int);
		VectorOnStackIterator&	operator--();
		VectorOnStackIterator&	operator--(int);

		ValueType&				operator[](int aIndex);
		ValueType&				operator*();
		ValueType*				operator->();

		bool					operator==(const VectorOnStackIterator& aOther) const;
		bool					operator!=(const VectorOnStackIterator& aOther) const;

	private:
		ValueType*	m_ptr;
	};

#pragma region		Method_Definitions

	template <class VectorOnStack>
	VectorOnStackIterator<VectorOnStack>::VectorOnStackIterator(ValueType* aPtr)
		: m_ptr{ aPtr }
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
	typename VectorOnStack::ValueType& VectorOnStackIterator<VectorOnStack>::operator[](int aIndex)
	{
		return *(m_ptr[aIndex]);
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
	bool VectorOnStackIterator<VectorOnStack>::operator==(const VectorOnStackIterator& aOther) const
	{
		return m_ptr == aOther.m_ptr;
	}

	template <class VectorOnStack>
	bool VectorOnStackIterator<VectorOnStack>::operator!=(const VectorOnStackIterator& aOther) const
	{
		return !(*this == aOther);
	}

#pragma endregion	Method_Definitions
}