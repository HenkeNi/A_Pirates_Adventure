#pragma once
#include <cassert>
#include <vector>
#include <iostream>

namespace Hi_Engine
{
	template <class T>
	class Heap
	{
	public:
		Heap();

		int				GetSize()						const;
		const T&		GetTop()						const;
		bool			IsEmpty()						const;
		void			Enqueue(const T& anElement);
		T				Dequeue();

	private:
		int				GetParent(int aCurrentIndex)	const;
		int				GetLeftChild(int anIndex)		const;
		int				GetRightChild(int anIndex)		const;
		void			Heapify(int anIndex);

		std::vector<T>	myNodes;
	};

	template <class T>
	Heap<T>::Heap()
	{
		myNodes.reserve(32);
	}

	template <class T>
	int Heap<T>::GetSize() const
	{
		return myNodes.size();
	}

	template <class T>
	const T& Heap<T>::GetTop() const
	{
		return myNodes.front();
	}

	template <class T>
	bool Heap<T>::IsEmpty() const
	{
		return myNodes.empty();
	}

	template <class T>
	void Heap<T>::Enqueue(const T& anElement)
	{
		myNodes.push_back(anElement);
		int index = myNodes.size() - 1;

		/* - Move element up tree (if larger than parent) - */
		while (index != 0 && myNodes[GetParent(index)] < myNodes[index])
		{
			std::swap(myNodes[GetParent(index)], myNodes[index]);
			index = GetParent(index);
		}
	}

	template <class T>
	T Heap<T>::Dequeue()
	{
		assert(!IsEmpty());

		T topElement = myNodes.front();
		std::swap(myNodes.front(), myNodes.back());
		myNodes.pop_back();

		Heapify(0);

		return topElement;
	}

	template <class T>
	int Heap<T>::GetParent(int aCurrentIndex) const
	{
		return (aCurrentIndex - 1) / 2;
	}

	template <class T>
	int	Heap<T>::GetLeftChild(int anIndex) const
	{
		return (anIndex * 2) + 1;
	}

	template <class T>
	int	Heap<T>::GetRightChild(int anIndex) const
	{
		return (anIndex * 2) + 2;
	}

	template <class T>
	void Heap<T>::Heapify(int anIndex)
	{
		int left = GetLeftChild(anIndex);
		int right = GetRightChild(anIndex);

		int largest = anIndex;

		if ((left < GetSize()) && myNodes[largest] < myNodes[left])
		{
			largest = left;
		}
		if ((right < GetSize()) && myNodes[largest] < myNodes[right])
		{
			largest = right;
		}

		if (largest != anIndex)
		{
			std::swap(myNodes[anIndex], myNodes[largest]);
			Heapify(largest);
		}
	}
}

/*
#pragma once
#include <cassert>

namespace CommonUtilities
{
	template <class T, bool Static = true, typename SizeType = unsigned int>
	class MinHeap
	{
	public:
		MinHeap(const SizeType aCapacity = 16);
		~MinHeap();

		const T& GetTop()					const;
		int			GetSize()					const;
		bool		IsEmpty()					const;
		bool		IsFull()					const;
		void		Enqueue(const T& aElement);
		T			Dequeue();
		void		RemoveCyclic(const T& aObject);
		void		RemoveCyclicAtIndnex(const SizeType aIndex);
		void		Resize(const SizeType aCapacity);

	private:
int			Parent(int aIndex)			const;
int			LeftChild(int aIndex)		const;
int			RightChild(int aIndex)		const;
void		HeapifyDown(int aIndex);
void		HeapifyUp(int aIndex);

T* myData;
SizeType	myCapacity;
SizeType	mySize;
	};

#pragma region METHOD_DEFINITIONS

	template <class T, bool Static, typename SizeType>
	MinHeap<T, Static, SizeType>::MinHeap(const SizeType aCapacity)
		: myData{ new T[aCapacity] }, myCapacity{ aCapacity }, mySize{ 0 }
	{
	}

	template <class T, bool Static, typename SizeType>
	MinHeap<T, Static, SizeType>::~MinHeap()
	{
		delete[] myData;
	}

	template <class T, bool Static, typename SizeType>
	const T& MinHeap<T, Static, SizeType>::GetTop()				const
	{
		return myData[0];
	}

	template <class T, bool Static, typename SizeType>
	int	MinHeap<T, Static, SizeType>::GetSize()					const
	{
		return mySize;
	}

	template <class T, bool Static, typename SizeType>
	bool MinHeap<T, Static, SizeType>::IsEmpty()				const
	{
		return mySize == 0;
	}

	template <class T, bool Static, typename SizeType>
	bool MinHeap<T, Static, SizeType>::IsFull()					const
	{
		return mySize == myCapacity;
	}

	template <class T, bool Static, typename SizeType>
	void MinHeap<T, Static, SizeType>::Enqueue(const T& aElement)
	{
		if (IsFull())
		{
			if (Static)
				assert(false && "MinHeap is full");
			else
				Resize(myCapacity * 2);
		}

		myData[mySize] = aElement;
		int index = mySize++;

		HeapifyUp(index);
	}

	template <class T, bool Static, typename SizeType>
	T MinHeap<T, Static, SizeType>::Dequeue()
	{
		assert(!IsEmpty());

		T minElement = GetTop();

		RemoveCyclicAtIndnex(0);
		HeapifyDown(0);

		return minElement;
	}

	template <class T, bool Static, typename SizeType>
	void MinHeap<T, Static, SizeType>::RemoveCyclic(const T& aObject)
	{
		int index = -1;
		for (int i = 0; i < mySize; ++i)
		{
			if (myData[i] == aObject)
			{
				index = i;
				break;
			}
		}

		if (index != -1)
			myData[index] = myData[--mySize];
	}

	template <class T, bool Static, typename SizeType>
	void MinHeap<T, Static, SizeType>::RemoveCyclicAtIndnex(const SizeType aIndex)
	{
		assert(aIndex >= 0 && aIndex < mySize);
		myData[aIndex] = myData[--mySize];
	}

	template <class T, bool Static, typename SizeType>
	void MinHeap<T, Static, SizeType>::Resize(const SizeType aCapacity)
	{
		assert(!Static && "MinHeap is not a dynamic structure!");

		T* temp = new T[aCapacity];
		for (SizeType i = 0; i < mySize; ++i)
		{
			temp[i] = myData[i];
		}

		delete[] myData;
		myData = temp;

		myCapacity = aCapacity;
	}

	template <class T, bool Static, typename SizeType>
	int MinHeap<T, Static, SizeType>::Parent(int aIndex)		const
	{
		return (aIndex - 1) / 2;
	}

	template <class T, bool Static, typename SizeType>
	int MinHeap<T, Static, SizeType>::LeftChild(int aIndex)		const
	{
		return (aIndex * 2) + 1;
	}

	template <class T, bool Static, typename SizeType>
	int MinHeap<T, Static, SizeType>::RightChild(int aIndex)	const
	{
		return (aIndex * 2) + 2;
	}

	template <class T, bool Static, typename SizeType>
	void MinHeap<T, Static, SizeType>::HeapifyDown(int aIndex)
	{
		int leftChild = LeftChild(aIndex);
		int rightChild = RightChild(aIndex);

		int smallest = aIndex;

		if (leftChild < (int)mySize && myData[leftChild] < myData[smallest])
		{
			smallest = leftChild;
		}
		if (rightChild < (int)mySize && myData[rightChild] < myData[smallest])
		{
			smallest = rightChild;
		}

		if (smallest != aIndex)
		{
			std::swap(myData[aIndex], myData[smallest]);
			HeapifyDown(smallest);
		}
	}

	template <class T, bool Static, typename SizeType>
	void MinHeap<T, Static, SizeType>::HeapifyUp(int aIndex)
	{
		if (aIndex >= 0 && myData[aIndex] < myData[Parent(aIndex)])
		{
			std::swap(myData[aIndex], myData[Parent(aIndex)]);
			HeapifyUp(Parent(aIndex));
		}
	}

#pragma endregion METHOD_DEFINITIONS
}
*/