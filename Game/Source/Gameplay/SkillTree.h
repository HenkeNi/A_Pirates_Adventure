#pragma once


class Skill // inheritance..?
{
};

struct SkillNode
{
	std::vector<SkillNode*> ChildNodes;

	unsigned RequiredLevel;
	bool IsUnlocked = false;


	//unsigned ID;
	std::string Identifier;
	std::any Data;
};


class SkillTree
{
public:
	SkillTree();
	~SkillTree();

	void RegisterSkill(SkillNode* aParent, /*const std::any& someData*/  const std::string& Identifier);
	void RegisterSkill(const std::string& aParentID,  /*const std::any& someData*/ const std::string& Identifier);

	SkillNode* GetRoot();

	void DebugLog();

	SkillNode* BreadthFirstSearch(const std::string& anIdentifier);

	std::vector<SkillNode*> GetNextUnlockableNodes();

	void Unlock(const std::string& anIdentifier);

	void PrintLevelOrder(SkillNode* aRoot);

private:
	void DeleteTree(SkillNode* aRoot);
	void InsertSkill(SkillNode* aRoot, const std::string& aParentID, SkillNode* aSkill);	// STORE ParentID?

	SkillNode* m_root;
};