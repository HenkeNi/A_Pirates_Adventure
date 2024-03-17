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
void SkillTree::RegisterSkill(SkillNode* parent, const std::string& identifier)
{
	if (parent)
	{
		auto* newSkill = new SkillNode;
		newSkill->IsUnlocked = false;
		//newSkill->Data = someData;
		newSkill->Identifier = identifier;

		parent->ChildNodes.push_back(newSkill);
	}
}

//void SkillTree::RegisterSkill(unsigned aParentID, const std::any& someData)
void SkillTree::RegisterSkill(const std::string& parentID, const std::string& identifier)
{
	if (!m_root)
		return;

	auto* newSkill = new SkillNode;
	newSkill->IsUnlocked = false;
	//newSkill->Data = someData;
	newSkill->Identifier = identifier;

	//static bool first = true;
	//if (first)
	//{
	//	newSkill->IsUnlocked = true;
	//	first = false;
	//}
	
	// Store parent ID??

	InsertSkill(m_root, parentID, newSkill);
}

SkillNode* SkillTree::GetRoot()
{
	return m_root;
}

void SkillTree::DebugLog()
{

}

SkillNode* SkillTree::BreadthFirstSearch(const std::string& identifier)
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

void SkillTree::Unlock(const std::string& identifier)
{

}

void SkillTree::PrintLevelOrder(SkillNode* root)
{
	if (!root)
		return;

	std::queue<SkillNode*> queue;
	queue.push(root);

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

void SkillTree::DeleteTree(SkillNode* root)
{
	if (!root)
		return;

	for (auto* child : root->ChildNodes)
		DeleteTree(child);

	delete root;
}

void SkillTree::InsertSkill(SkillNode* root, const std::string& parentID, SkillNode* skill)
{
	if (!root)
		return;

	if (root->Identifier == parentID)
	{
		root->ChildNodes.push_back(skill);
	}
	else
	{
		for (auto* child : root->ChildNodes)
		{
			InsertSkill(child, parentID, skill);
		}
	}
}