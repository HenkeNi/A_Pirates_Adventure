#pragma once

namespace CU = CommonUtilities;

class Component;

class ComponentFactory
{
public:
	ComponentFactory();
	~ComponentFactory();

	Component*	CreateComponent(const std::string& aType);
	
	void		Init();
	bool		RegisterComponent(const std::string& aType, Component* aComponent);
	bool		Contains(const std::string& aType) const;

private:
	std::unordered_map<std::string, Component*>	m_components;
	//CU::MemoryPool<Component>					m_memoryPool;	 // POSSIBLE TO Use memory pool with derived class???  -> or use allocator placement new??
};