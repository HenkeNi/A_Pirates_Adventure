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

// Make a system?
class SkillTree
{
public:
	SkillTree();
	~SkillTree();

	void RegisterSkill(SkillNode* parent, /*const std::any& data*/  const std::string& identifier);
	void RegisterSkill(const std::string& parentID,  /*const std::any& data*/ const std::string& identifier);

	SkillNode* GetRoot();

	void DebugLog();

	SkillNode* BreadthFirstSearch(const std::string& identifier);

	std::vector<SkillNode*> GetNextUnlockableNodes();

	void Unlock(const std::string& identifier);

	void PrintLevelOrder(SkillNode* root);

private:
	void DeleteTree(SkillNode* root);
	void InsertSkill(SkillNode* root, const std::string& parentID, SkillNode* skill);	// STORE ParentID?

	SkillNode* m_root;
};