#pragma once

namespace CU = CommonUtilities;

class Component;

class ComponentFactory
{
public:
	Component* CreateComponent(const std::string& aType);	// perfect forwarding?? -> pass in addtional data (call compoenet->Init() and pass it in??)

	bool RegisterComponent(const std::string& aType, Component* aComponent);
	bool Contains(const std::string& aType) const;

private:
	std::unordered_map<std::string, Component*> m_components;
	//CU::MemoryPool<Component> m_memoryPool;
};

