#pragma once

//namespace CU = CommonUtilities;
//
//class Component;
//
//// use builder??
//
//class ComponentRegistry
//{
//public:
//	ComponentRegistry(const ComponentRegistry&) = delete;
//	ComponentRegistry& operator=(const ComponentRegistry&) = delete;
//
//	static ComponentRegistry& GetInstance();
//
//	template <typename ComponentType>
//	CU::MemoryPool<ComponentType>& GetMemoryPool();
//
//	template <typename ComponentType>
//	void RegisterComponentType();
//
//
//	template <typename ComponentType>
//	ComponentType* CreateComponentOfType();
//
//	//static RegisterComponent();	
//
//private:
//	ComponentRegistry() = default;
//
//	//static std::unordered_map<std::string, Component*> s_registeredComponents;
//
//	// static std::unordered_map<std::string, std::type_index> s_registeredComponents;
//	//static std::unordered_map<std::string, std::type_index> s_registeredComponents;
//};
//
//
//template <typename ComponentType>
//CU::MemoryPool<ComponentType>& ComponentRegistry::GetMemoryPool()
//{
//	static CU::MemoryPool<ComponentType> memoryPool; // Maybe??
//	return memoryPool;
//}
//
//template <typename ComponentType>
//void ComponentRegistry::RegisterComponentType()
//{
//
//}
//
//template <typename ComponentType>
//ComponentType* ComponentRegistry::CreateComponentOfType()
//{
//	return nullptr;
//}