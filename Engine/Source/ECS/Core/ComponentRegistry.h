#pragma once
#include "../Utility/ECSTypes.h"
#include "../../Core/Utility/TypeTraits.h"
#include <typeindex>
#include <cstddef>

namespace Hi_Engine
{
    struct ComponentData
    {
        ComponentID id;
        ::std::type_index type; // needed? or use as key instead?

        ::std::size_t size; // size in bytes
        ::std::size_t alignment;


        const char* name;

        // std::function<void(void*)> destructor;
        // initializer? add component?
    };

	// singelton or all static?
    class ComponentRegistry
    {
    public:
        template <ComponentType T>
        void RegisterComponent(const char* name);

        template <typename T>
        bool IsRegistered()
        {
            return m_typeToComponentData.find(typeid(T)) != m_typeToComponentData.end();
        }

        template <ComponentType... Ts>
        Signatures GetSignature() const
        {
            Signature signature{};
            (signature.set(GetComponentID<Ts>()), ...);

            return signature;
        }

        const ComponentData& GetComponentDataByID(ComponentID id) const // return pointer instead??
        {
            assert(m_idToComponentData.contains(id) && "Id not found");
            return *m_idToComponentData.at(id);
        }

        const ComponentData& GetComponentDataByType(::std::type_index type) const
        {
            assert(m_typeToComponentData.contains(type) && "Id not found");
            return m_typeToComponentData.at(type);
        }

        const ComponentData& GetComponentDataByName(const char* name) const
        {
            assert(m_nameToComponentData.contains(name) && "Failed!!!!"); // this?
            return *m_nameToComponentData.at(name);
        }

        template <ComponentType T>
        const ComponentData& GetComponentData() const
        {
            return GetComponentDataByType(typeid(T));
        }


        // get component data by name?


        template <ComponentType T>
        ComponentID GetComponentID() const // use id generator class?
        {
            static const ComponentID id = GenerateID();
            return id;
        }

    private:
        ComponentID GenerateID() const
        {
            static ComponentID id = 0;
            return id++;
        }

        std::unordered_map<std::type_index, ComponentData> m_typeToComponentData;
        std::unordered_map<ComponentID, ComponentData*> m_idToComponentData;
        std::unordered_map<std::string, ComponentData*> m_nameToComponentData;
    };

#pragma region Templated_Methods
    
    template <ComponentType T>
    void ComponentRegistry::RegisterComponent(const char* name)
    {
        auto id = GetComponentID<T>();
        std::type_index type = typeid(T);

        ComponentData data{
            id,
            type,
            sizeof(T),
            alignof(T),
            name
           // [](void* ptr) { static_cast<T*>(ptr)->~T(); }
        };

        const auto& [it, success] = m_typeToComponentData.insert({ type, std::move(data) });

        if (success)
        {
            m_idToComponentData.insert({ id, &it->second });
            m_nameToComponentData.insert({ name, &it->second });
        }
        else
        {
            Logger::LogWarning("[ComponentRegistry::RegisterComponent] - Failed to insert component type");
        }
    }
   
#pragma endregion
}