#include "Pch.h"
#include "SkillTree.h"


SkillTree::SkillTree()
	: m_root{ new SkillNode }
{
	m_root->IsUnlocked = true;
	m_root->Identifier = "Base";
}

SkillTree::~SkillTree()
{
	DeleteTree(m_root);
}

//void SkillTree::RegisterSkill(SkillNode* aParent, const std::any& someData)
void SkillTree::RegisterSkill(SkillNode* aParent, const std::string& Identifier)
{
	if (aParent)
	{
		auto* newSkill = new SkillNode;
		newSkill->IsUnlocked = false;
		//newSkill->Data = someData;
		newSkill->Identifier = Identifier;

		aParent->ChildNodes.push_back(newSkill);
	}
}

//void SkillTree::RegisterSkill(unsigned aParentID, const std::any& someData)
void SkillTree::RegisterSkill(const std::string& aParentID, const std::string& Identifier)
{
	if (!m_root)
		return;

	auto* newSkill = new SkillNode;
	newSkill->IsUnlocked = false;
	//newSkill->Data = someData;
	newSkill->Identifier = Identifier;

	//static bool first = true;
	//if (first)
	//{
	//	newSkill->IsUnlocked = true;
	//	first = false;
	//}
	
	// Store parent ID??

	InsertSkill(m_root, aParentID, newSkill);
}

SkillNode* SkillTree::GetRoot()
{
	return m_root;
}

void SkillTree::DebugLog()
{

}

SkillNode* SkillTree::BreadthFirstSearch(const std::string& anIdentifier)
{
	return nullptr;
}

std::vector<SkillNode*> SkillTree::GetNextUnlockableNodes()
{
	if (!m_root)
		return {};

	std::vector<SkillNode*> unlockableNodes;

	std::queue<SkillNode*> queue;
	queue.push(m_root);

	while (!queue.empty())
	{
		SkillNode* node = queue.front();

		if (!node->IsUnlocked)
			unlockableNodes.push_back(node);

		queue.pop();

		if (node->IsUnlocked)
		{
			for (auto* child : node->ChildNodes)
			{
				queue.push(child);
			}
		}
	}

	return unlockableNodes;
}

void SkillTree::Unlock(const std::string& anIdentifier)
{

}

void SkillTree::PrintLevelOrder(SkillNode* aRoot)
{
	if (!aRoot)
		return;

	std::queue<SkillNode*> queue;
	queue.push(aRoot);

	while (!queue.empty())
	{
		SkillNode* node = queue.front();
		std::cout << node->Identifier << ' ';

		queue.pop();

		for (auto* child : node->ChildNodes)
		{
			queue.push(child);
		}
	}
}

void SkillTree::DeleteTree(SkillNode* aRoot)
{
	if (!aRoot)
		return;

	for (auto* child : aRoot->ChildNodes)
		DeleteTree(child);

	delete aRoot;
}

void SkillTree::InsertSkill(SkillNode* aRoot, const std::string& aParentID, SkillNode* aSkill)
{
	if (!aRoot)
		return;

	if (aRoot->Identifier == aParentID)
	{
		aRoot->ChildNodes.push_back(aSkill);
	}
	else
	{
		for (auto* child : aRoot->ChildNodes)
		{
			InsertSkill(child, aParentID, aSkill);
		}
	}
}