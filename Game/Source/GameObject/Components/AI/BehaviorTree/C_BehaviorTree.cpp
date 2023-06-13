#include "Pch.h"
#include "C_BehaviorTree.h"
#include "../AI/BehaviorTree/BehaviorTreeNode.h"


C_BehaviorTree::C_BehaviorTree(GameObject* anOwner)
	: Component{ anOwner }, m_root{ nullptr }
{
}

C_BehaviorTree::~C_BehaviorTree()
{
}

void C_BehaviorTree::Init(rapidjson::Value& aValue)	{}

void C_BehaviorTree::HandleMessage(const CompMessage& aMsg) {}

void C_BehaviorTree::Update(float aDeltaTime)
{
	// DO in late update instead??
	if (m_root)
		m_root->Execute(m_owner);
}

C_BehaviorTree* C_BehaviorTree::Copy() const
{
	auto* res = CU::MemoryPool<C_BehaviorTree>::GetInstance().GetResource();	// TODO; register in ComponentManager?
	assert(res && "Memory Pool returned invalid memory");

	return new (res) C_BehaviorTree{ *this };
}

void C_BehaviorTree::SetRootNode(BehaviorTreeNode* aNode)
{
	if (m_root)
		delete m_root;

	m_root = aNode;
}

void C_BehaviorTree::Clear()
{
	if (m_root)
		m_root->Clear();

	delete m_root;
	m_root = nullptr;
}