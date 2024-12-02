#pragma once
#include <iostream>
#include <cmath>

namespace Hi_Engine
{
	template <typename T>
	bool IsEqual(const T& aFirst, const T& aSecond)
	{
		return (!(aFirst < aSecond) && !(aSecond < aFirst));
	}

	template <class T>
	struct BinaryTreeNode
	{
		BinaryTreeNode(T someData)
			: myData{ someData }, myLeftChild{ nullptr }, myRightChild{ nullptr }
		{
		}

		T					myData;
		BinaryTreeNode* myLeftChild;
		BinaryTreeNode* myRightChild;
	};

	template <class T>
	class BinaryTree
	{
	public:
		BinaryTree();
		~BinaryTree();

		const BinaryTreeNode<T>* GetRoot() const;
		bool						HasElement(const T& aValue);
		void						Insert(const T& aValue);
		void						Remove(const T& aValue);
		void						DSWBalance();

	private:
		/* - Methods - */
		void						DeleteTree(BinaryTreeNode<T>* aNode);


		int							CreateBackbone(BinaryTreeNode<T>* aGrandParent);
		void						Compress(BinaryTreeNode<T>* aGrandParent, int m);

		//void						CreateBalancedTree();
		//void						RotateRight(BinaryTreeNode<T>* aNode);
		/*BinaryTreeNode<T>*			BalanceVine(BinaryTreeNode<T>* aRoot, int aNodeCount);
		int							GetNodeCount(BinaryTreeNode<T>* aRoot);
		BinaryTreeNode<T>*			CreateRightVine(BinaryTreeNode<T>* aRoot);
		BinaryTreeNode<T>*			RotateRight(BinaryTreeNode<T>* aNode);*/




		BinaryTreeNode<T>* Search(BinaryTreeNode<T>* aNode, const T& aValue);
		BinaryTreeNode<T>* Insert(BinaryTreeNode<T>* aNode, const T& aValue);
		BinaryTreeNode<T>* Delete(BinaryTreeNode<T>* aNode, const T& aValue);
		BinaryTreeNode<T>* FindMin(BinaryTreeNode<T>* aNode);

		/* - Data Members - */
		BinaryTreeNode<T>* myRoot;
	};

	template <class T>
	BinaryTree<T>::BinaryTree()
		: myRoot{ nullptr }
	{
	}

	template <class T>
	BinaryTree<T>::~BinaryTree()
	{
		DeleteTree(myRoot);
	}

	template <class T>
	const BinaryTreeNode<T>* BinaryTree<T>::GetRoot() const
	{
		return myRoot;
	}

	template <class T>
	bool BinaryTree<T>::HasElement(const T& aValue)
	{
		bool found = Search(myRoot, aValue) != nullptr;
		return found;
	}

	template <class T>
	void BinaryTree<T>::Insert(const T& aValue)
	{
		if (!HasElement(aValue))
		{
			myRoot = Insert(myRoot, aValue);
		}
	}

	template <class T>
	void BinaryTree<T>::Remove(const T& aValue)
	{
		myRoot = Delete(myRoot, aValue);
	}

	template <class T>
	void BinaryTree<T>::DSWBalance()
	{
		BinaryTreeNode<T>* grandParent = new BinaryTree<T>();
		grandParent->myRightChild = myRoot;

		int count = CreateBackbone(grandParent);
		int treeHeight = log2(count + 1);

		int nodesAmount = pow(2, treeHeight) - 1;

		Compress(grandParent, count - nodesAmount);

		for (nodesAmount = nodesAmount / 2; nodesAmount > 0; nodesAmount /= 2)
		{
			Compress(grandParent, nodesAmount);
		}

		myRoot = grandParent->myRightChild;
		//CreateBackbone(myRoot);
		//CreateBalancedTree();
	}

	/* -------------- Private ----------------- */
	template <class T>
	void BinaryTree<T>::DeleteTree(BinaryTreeNode<T>* aNode)
	{
		if (aNode == nullptr)
		{
			return;
		}

		DeleteTree(aNode->myLeftChild);
		DeleteTree(aNode->myRightChild);

		delete aNode;
		aNode = nullptr;
	}





	template <class T>
	int BinaryTree<T>::CreateBackbone(BinaryTreeNode<T>* aGrandParent)
	{
		int count = 0;
		BinaryTreeNode<T>* tempNode = aGrandParent->myRightChild;

		while (tempNode)
		{
			/* if a left node exits => right rotate it */
			if (tempNode->myLeftChild != nullptr)
			{
				BinaryTreeNode<T>* oldTemp = tempNode;
				tempNode = tempNode->myLeftChild;
				oldTemp->myLeftChild = tempNode->myRightChild;
				tempNode->myRightChild = oldTemp;
				aGrandParent->myRightChild = tempNode;
			}
			else
			{
				++count;
				aGrandParent = tempNode;
				tempNode = tempNode->myRightChild;
			}
		}
		return count;


		/*auto* currentNode = myRoot;
		while (currentNode != nullptr)
		{
			if (currentNode->myLeftChild != nullptr)
			{
				RotateRight(currentNode);
			}

			currentNode = currentNode->myRightChild;
		}*/

		//int count = 0;

		//auto* temp = aGrandParent->myRightChild;
		//while (temp)
		//{
		//	if (temp->myLeftChild)
		//	{
		//		// RotateRight(tempNode);
		//		auto* oldTemp = temp;
		//		temp = temp->myLeftChild;
		//		oldTemp->myLeftChild = temp->myRightChild;
		//		temp->myRightChild = oldTemp;
		//		aGrandParent->myRightChild = temp;
		//		
		//	}
		//	else
		//	{
		//		++count;
		//		aGrandParent = temp;
		//		temp = temp->myRightChild;
		//	}
		//}
		//return count;

		//auto* tempNode = aGrandParent->myRightChild;
		//while (tempNode != nullptr)
		//{
		//	while (tempNode->myLeftChild != nullptr)
		//	{
		//		RotateRight(tempNode);
		//	}
		//	tempNode = tempNode->myRightChild;
		//}
	}

	template <class T>
	void BinaryTree<T>::Compress(BinaryTreeNode<T>* aGrandParent, int m)
	{
		BinaryTreeNode<T>* tempNode = aGrandParent->myRightChild;

		for (int i = 0; i < m; ++i)
		{
			BinaryTreeNode<T>* oldTemp = tempNode;
			tempNode = tempNode->myRightChild;
			aGrandParent->myRightChild = tempNode;
			oldTemp->myRightChild = tempNode->myLeftChild;
			tempNode->myLeftChild = oldTemp;
			aGrandParent = tempNode;
			tempNode = tempNode->myRightChild;
		}
	}

	//template <class T>
	//void RotateRight(BinaryTreeNode<T>* aGrandParent, BinaryTreeNode<T>* aParent, BinaryTreeNode<T>* aChild)
	//{
	//	if (aGrandParent != nullptr)
	//	{
	//		aGrandParent->myRightChild = aChild;
	//	}
	//}








	//template <class T>
	//BinaryTreeNode<T>* BinaryTree<T>::BalanceVine(BinaryTreeNode<T>* aRoot, int aNodeCount)
	//{
	//	int times = (int)log(aNodeCount, 2);
	//	auto* newRoot = aRoot;
	//	for (int i = 0; i < times; ++i)
	//	{
	//			newRoot = RotateLeft(newRoot);
	//			aRoot = newRoot->myRightChild;
	//			for (int j = 0; j < aNodeCount / 2 - 1; ++j)
	//			{
	//				aRoot = RotateLeft(aRoot);
	//				aRoot = aRoot->myRightChild;
	//			}
	//			aNodeCount >>= 1;
	//	}
	//	return newRoot;
	//}

	//template <class T>
	//int BinaryTree<T>::GetNodeCount(BinaryTreeNode<T>* aRoot)
	//{
	//	if (aRoot == nullptr)
	//	{
	//		return 0;
	//	}
	//	int i = 1;
	//	while (aRoot->myRightChild != nullptr)
	//	{
	//		aRoot = aRoot->myRightChild;
	//		++i;
	//	}
	//	return i;
	//}

	//template <class T>
	//BinaryTreeNode<T>* BinaryTree<T>::CreateRightVine(BinaryTreeNode<T>* aRoot)
	//{
	//	while (aRoot->myLeftChild != nullptr)
	//	{
	//		aRoot = RotateRight(aRoot);
	//	}
	//	if (aRoot->myRightChild != nullptr)
	//	{
	//		aRoot->myRightChild = CreateRightVine(aRoot->myRightChild);
	//	}
	//	return aRoot;
	//}


	//template <class T>
	//BinaryTreeNode<T>* BinaryTree<T>::RotateRight(BinaryTreeNode<T>* aNode)
	//{
	//	if (aNode != nullptr)
	//	{
	//		auto* left = aNode->myLeftChild;
	//		aNode->myLeftChild = left->myleftChild;
	//		left->myLeftChild = left->myRightChild;
	//		left->myRightChild = aNode->myRightChild;
	//		aNode->myRightChild = left;

	//		T tempData = aNode->myData;
	//		aNode->myData = left.myData;
	//		left->myData = tempData;

	//	}
	//	return aNode;
	//}

	//template <class T>
	//bool BinaryTree<T>::RotateRight(BinaryTreeNode<T>* aNode)
	//{
	//	if (aNode == nullptr || aNode->myLeftChild == nullptr) 
	//	{ 
	//		return false;
	//	}

	//	const T tempData = aNode->myData;
	//	aNode->myData = aNode->myLeftChild->myData;
	//	aNode->myLeftChild->myData = tempData;


	//	BinaryTreeNode<T>* originalLeft = aNode->myLeftChild;
	//	aNode->myLeftChild = originalLeft->myLeftChild;
	//	originalLeft->myLeftChild = originalLeft->myRightChild;
	//	originalLeft->myRightChild = aNode->myRightChild;
	//	aNode->myRightChild = originalLeft;

	//	return true;
	//}


	//template <class T>
	//void BinaryTree<T>::CreateBalancedTree()
	//{


	//	//auto* tmpNode = myRoot;
	//	//auto* tmpNode2 = tmpNode->myRightChild->myRightChild;

	//	//while (tmpNode != nullptr)
	//	//{
	//	//	if (tmpNode2 != nullptr && tmpNode2->myRightChild != nullptr)
	//	//	{
	//	//		tmpNode->myRightChild = tmpNode->myRightChild->myLeftChild;
	//	//		tmpNode->myRightChild->myLeftChild = tmpNode;
	//	//		tmpNode = tmpNode->myRightChild;
	//	//		tmpNode->myRightChild = tmpNode->myRightChild->myRightChild;

	//	//		tmpNode2->myRightChild->myLeftChild = tmpNode2;
	//	//		tmpNode2->myRightChild = nullptr;
	//	//		tmpNode2 = tmpNode->myRightChild->myRightChild;
	//	//	}
	//	//	else
	//	//	{
	//	//		break;
	//	//	}
	//	//}
	//}

	template <class T>
	BinaryTreeNode<T>* BinaryTree<T>::Search(BinaryTreeNode<T>* aNode, const T& aValue)
	{
		if (aNode == nullptr || Utility::IsEqual(aNode->myData, aValue))
		{
			return aNode;
		}

		return aNode->myData < aValue ? Search(aNode->myRightChild, aValue) : Search(aNode->myLeftChild, aValue);
	}

	template <class T>
	BinaryTreeNode<T>* BinaryTree<T>::Insert(BinaryTreeNode<T>* aNode, const T& aValue)
	{
		if (aNode == nullptr)
		{
			return new BinaryTreeNode<T>(aValue);
		}

		if (aValue < aNode->myData) /* - Value smaller than current node's value - */
		{
			aNode->myLeftChild = Insert(aNode->myLeftChild, aValue);
		}
		else if (aNode->myData < aValue) /* - Value larger than current node's value - */
		{
			aNode->myRightChild = Insert(aNode->myRightChild, aValue);
		}
		return aNode;
	}

	template <class T>
	BinaryTreeNode<T>* BinaryTree<T>::Delete(BinaryTreeNode<T>* aNode, const T& aValue)
	{
		if (aNode == nullptr)
			return aNode;

		if (aValue < aNode->myData)
		{
			aNode->myLeftChild = Delete(aNode->myLeftChild, aValue);
		}
		else if (!Utility::IsEqual(aNode->myData, aValue))
		{
			aNode->myRightChild = Delete(aNode->myRightChild, aValue);
		}
		else
		{
			/* - No Child - */
			if (aNode->myLeftChild == nullptr && aNode->myRightChild == nullptr)
			{
				delete aNode;
				aNode = nullptr;
			}
			else if (aNode->myLeftChild == nullptr)
			{
				auto* tempNode = aNode->myRightChild;
				delete aNode;

				aNode = tempNode;
			}
			else if (aNode->myRightChild == nullptr)
			{
				auto* tempNode = aNode->myLeftChild;
				delete aNode;

				aNode = tempNode;
			}
			else /* - Two children - */
			{
				auto* tempNode = FindMin(aNode->myRightChild);
				aNode->myData = tempNode->myData;
				aNode->myRightChild = Delete(aNode->myRightChild, tempNode->myData);
			}
		}
		return aNode;
	}

	template <class T>
	BinaryTreeNode<T>* BinaryTree<T>::FindMin(BinaryTreeNode<T>* aNode)
	{
		while (aNode->myLeftChild != nullptr)
		{
			aNode = aNode->myLeftChild;
		}

		return aNode;
	}
}