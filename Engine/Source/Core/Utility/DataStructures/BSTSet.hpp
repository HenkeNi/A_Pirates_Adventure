#pragma once

template <typename T>
struct TreeNode
{
	T Data;
	TreeNode* LeftChild;
	TreeNode* RightChild;
};


template <typename T>
bool IsEqual(const T& aFirst, const T& aSecond)
{
	return (!(aFirst < aSecond) && !(aSecond < aFirst));
}

template <typename T>
class BSTSet
{
public:
	BSTSet();
	~BSTSet();

	bool HasElement(const T& value);
	void Insert(const T& value);
	void Remove(const T& value);
	
	void DebugLog();
	void Clear(TreeNode<T>* node);

	// breadth first & depth first

private:
	TreeNode<T>* Search(TreeNode<T>* node, const T& value);
	TreeNode<T>* Insert(TreeNode<T>* parent, const T& value);
	TreeNode<T>* Remove(TreeNode<T>* parent, const T& value);
	TreeNode<T>* FindMin(TreeNode<T>* node);


	TreeNode<T>* m_root;
};

#pragma region Constructors

template <typename T>
BSTSet<T>::BSTSet()
	: m_root{ nullptr }
{
}

template <typename T>
BSTSet<T>::~BSTSet()
{
	Clear(m_root);
}

#pragma endregion Constructors

#pragma region Method_Definitions

template <typename T>
bool BSTSet<T>::HasElement(const T& value)
{
	auto* found = Search(m_root, value);

	return found != nullptr;
}

template <typename T>
void BSTSet<T>::Insert(const T& value)
{
	m_root = Insert(m_root, value);
}

template <typename T>
void BSTSet<T>::Remove(const T& value)
{
	m_root = Remove(m_root, value);
}

template<typename T>
inline void BSTSet<T>::DebugLog()
{
	auto* node = m_root;
	while (node)
	{
		if (node->LeftChild)
		{

		}
		else if (node->RightChild)
		{

		}
	}
}

template<typename T>
void BSTSet<T>::Clear(TreeNode<T>* node)
{
}

template<typename T>
TreeNode<T>* BSTSet<T>::Search(TreeNode<T>* node, const T& value)
{
	if (!node || IsEqual(node->Data, value))
		return node;

	return value < node->Data ? Search(node->LeftChild, value) : Search(node->RightChild, value);
}

template<typename T>
TreeNode<T>* BSTSet<T>::Insert(TreeNode<T>* parent, const T& value)
{
	if (!parent)
	{
		return new TreeNode<T>{ value, nullptr, nullptr };
	}

	if (value < parent->Data)
	{
		parent->LeftChild = Insert(parent->LeftChild, value);
	}
	else if (value > parent->Data)
	{
		parent->RightChild = Insert(parent->RightChild, value);
	}

	return parent;
}

template<typename T>
inline TreeNode<T>* BSTSet<T>::Remove(TreeNode<T>* parent, const T& value)
{
	if (parent == nullptr)
		return parent;

	if (value < parent->Data)
	{
		parent->LeftChild = Remove(parent->LeftChild, value);
	}
	else if (value > parent->Data)
	{
		parent->RightChild = Remove(parent->RightChild, value);
	}
	else
	{
		/* - Two children - */
		if (parent->LeftChild && parent->RightChild)
		{
			auto* temp = FindMin(parent->RightChild);
			parent->myData = temp->Data;
			parent->RightChild = Remove(parent->RightChild, temp->Data);
		}
		else if (!parent->LeftChild && !parent->RightChild) /* No children */
		{
			delete parent;
			parent = nullptr;
		}
		else
		{
			auto* temp = parent->RightChild ? parent->RightChild : parent->LeftChild;
			delete parent;

			parent = temp;
		}
	}
	return parent;
}

template<typename T>
inline TreeNode<T>* BSTSet<T>::FindMin(TreeNode<T>* node)
{
	while (node->LeftChild != nullptr)
	{
		node = node->LeftChild;
	}

	return node;
}

#pragma endregion Method_Definitions