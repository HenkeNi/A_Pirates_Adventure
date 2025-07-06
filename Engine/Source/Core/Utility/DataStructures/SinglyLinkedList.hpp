#pragma once
#include "SinglyLinkedListNode.hpp"
#include <cassert>

namespace Hi_Engine
{
	template <class Type, typename SizeType = unsigned>
	class SinglyLinkedList
	{
	public:
		using Node = SinglyLinkedListNode<Type>;

	public:
		SinglyLinkedList();
		~SinglyLinkedList();

		Node*		FindFirst(const Type& value);
		Node*		FindLast(const Type& value);
		Node*		GetFirst();
		Node*		GetLast();
		bool		IsEmpty()				const;
		SizeType	Size()					const;

		void		InsertFirst(const Type& value);
		void		InsertLast(const Type& value);
		void		InsertBefore(Node* node, const Type& value);
		void		InsertAfter(Node* node, const Type& value);

		void		RemoveFirst(const Type& value);
		void		RemoveLast(const Type& value);
		void		Remove(Node* node);
		void		Reverse();
		void		Clear();

		// iterator??

	private:
		Node*		m_head;
		SizeType	m_size;
	};

#pragma region Constructor

	template <class Type, typename SizeType>
	SinglyLinkedList<Type, SizeType>::SinglyLinkedList()
		: m_head{ nullptr }, m_size{ 0 }
	{
	}

	template <class Type, typename SizeType>
	SinglyLinkedList<Type, SizeType>::~SinglyLinkedList()
	{
		Clear();
	}

#pragma endregion Constructor

#pragma region Method_Definitions

	template <class Type, typename SizeType>
	SinglyLinkedListNode<Type>* SinglyLinkedList<Type, SizeType>::FindFirst(const Type& value)
	{
		assert(!IsEmpty() && "SinglyLinkedList is empty");

		auto* traverser = m_head;
		while (traverser != nullptr)
		{
			if (traverser->m_data == value)
			{
				return traverser;
			}
			traverser = traverser->m_nextNode;
		}
		return nullptr;
	}

	template <class Type, typename SizeType>
	SinglyLinkedListNode<Type>* SinglyLinkedList<Type, SizeType>::FindLast(const Type& value)
	{
		 
		Node* last = nullptr;
		
		auto* traverser = m_head;
		while (traverser != nullptr)
		{
			if (traverser->m_data == value)
			{
				last = traverser;
			}
			traverser = traverser->m_nextNode;
		}
		return last;
	}
	
	template <class Type, typename SizeType>
	SinglyLinkedListNode<Type>* SinglyLinkedList<Type, SizeType>::GetFirst()
	{
		return m_head;
	}

	template <class Type, typename SizeType>
	SinglyLinkedListNode<Type>* SinglyLinkedList<Type, SizeType>::GetLast()
	{
		if (!IsEmpty())
		{
			auto* traverser = m_head;
			while (traverser->m_nextNode != nullptr)
			{
				traverser = traverser->m_nextNode;
			}
			return traverser;
		}			
		return nullptr;
	}

	template <class Type, typename SizeType>
	bool SinglyLinkedList<Type, SizeType>::IsEmpty() const
	{
		return m_head == nullptr;
	}

	template <class Type, typename SizeType>
	SizeType SinglyLinkedList<Type, SizeType>::Size() const
	{
		return m_size;
	}

	template <class Type, typename SizeType>
	void SinglyLinkedList<Type, SizeType>::InsertFirst(const Type& value)
	{
		auto* newNode = new Node(value);
		newNode->m_nextNode = m_head;

		m_head = newNode;
		++m_size;
	}

	template <class Type, typename SizeType>
	void SinglyLinkedList<Type, SizeType>::InsertLast(const Type& value)
	{
		if (!IsEmpty())
		{
			auto* newNode = new Node(value);
			GetLast()->m_nextNode = newNode;

			++m_size;
		}
		else
		{
			InsertFirst(value);
		}
	}

	template <class Type, typename SizeType>
	void SinglyLinkedList<Type, SizeType>::InsertBefore(Node* aNode, const Type& value)
	{
		assert(aNode != nullptr && "Can't insert before nullptr");

		if (aNode == m_head)
		{
			InsertFirst(value);
			return;
		}

		auto* traverser = m_head;
		while (traverser->m_nextNode != nullptr)
		{
			if (traverser->m_nextNode == aNode)
			{
				auto* newNode = new Node(value);
				traverser->m_nextNode = newNode;

				newNode->m_nextNode = aNode;

				break;
			}
		}
	}

	template <class Type, typename SizeType>
	void SinglyLinkedList<Type, SizeType>::InsertAfter(Node* aNode, const Type& value)
	{


	}

	template <class Type, typename SizeType>
	void SinglyLinkedList<Type, SizeType>::RemoveFirst(const Type& value)
	{
	}

	template <class Type, typename SizeType>
	void SinglyLinkedList<Type, SizeType>::RemoveLast(const Type& value)
	{
	}

	template <class Type, typename SizeType>
	void SinglyLinkedList<Type, SizeType>::Remove(Node* aNode)
	{
	}


	template <class Type, typename SizeType>
	void SinglyLinkedList<Type, SizeType>::Reverse()
	{
		auto* traveler = m_head;
		while (traveler != nullptr)
		{

		}
	}


	template <class Type, typename SizeType>
	void SinglyLinkedList<Type, SizeType>::Clear()
	{
		m_size = 0;
	}

#pragma endregion Method_Definitions
}