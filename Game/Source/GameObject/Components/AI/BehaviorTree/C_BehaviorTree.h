#pragma once
#include "../../Component.h"

class BehaviorTreeNode;

class C_BehaviorTree : public Component
{
public:
	C_BehaviorTree(GameObject* anOwner = nullptr);
	~C_BehaviorTree();

	void			Init(rapidjson::Value& aValue)			override;
	void			HandleMessage(const CompMessage& aMsg)	override;
	void			Update(float aDeltaTime)				override;
	C_BehaviorTree*	Copy()							  const override;

	void			SetRootNode(BehaviorTreeNode* aNode);
	void			Clear();

private:
	BehaviorTreeNode* m_root;
};