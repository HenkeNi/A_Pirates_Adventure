#pragma once
#include <Core/CoreComponents.h>
#include "../Builders/ComponentBaseBuilder.hpp"


//namespace
//{
//    using ComponentData_t = std::unordered_map<std::string, std::any>;
//}
//
//class ComponentFactory
//{
//public:
//    ComponentBase* Create(const std::string& aType, const ComponentData_t& someData)  // or return a ComponentBase*
//    {
//        auto* component = s_componentBuilders.Build(aType);
//
//
//        auto sT = std::type_index(typeid(component));
//
//        InitializeComponent<sT>(component, someData);
//
//        return component;
//    }
//
//
//    //template <typename... Args>
//    //ComponentBase* Create(const std::string& aType, Args&&... args)  // or return a ComponentBase*
//    //{
//    //    //auto* component = CU::MemoryPool<T>::GetInstance().GetResource();
//
//    //    auto* component = s_componentBuilders.Build(aType);
//
//    //    // auto* component = CU::MemoryPool<T>::GetInstance().GetResource();
//
//    //    auto sT = std::type_index(typeid(component));
//
//    //    InitializeComponent<sT>(component, std::forward<Args>(args)...);
//
//    //    return component;
//    //}
//
//    static void	RegisterComponentBuilder(const std::string&aType, ComponentBaseBuilder* aBuilder);
//  /*  template <typename T, typename... Args>
//    T* CreateComponent(Args&&... args)
//    {
//        T* component = new T();
//
//        InitializeComponent(component, std::forward<Args>(args)...);
//
//        return component;
//    }*/
//
//private:
//    template<typename T, typename... Args>
//    void InitializeComponent(T* component, Args&&... args)
//    {
//        // Default implementation for components without explicit initialization logic
//        // You can provide a default behavior or leave it empty if no initialization is required
//    }
//
//    // Specialize the InitializeComponent function for specific component types that require initialization
//    template<typename... Args>
//    void InitializeComponent<TransformComponent>(TransformComponent* component, Args&&... args)
//    {
//
//        auto arguments = args;
//
//        int x = 10;
//        x += 10;
//
//        // Custom initialization logic for the TransformComponent using the provided arguments
//        // Set properties such as position, scale, rotation, etc.
//    }
//
//    static CU::Factory<ComponentBaseBuilder, ComponentBase>	s_componentBuilders;
//};