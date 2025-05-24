#pragma once
#include "../Utility/ECSTypes.h"
#include "../../Core/Utility/TypeTraits.h"
#include "Logging/Logger.h"
#include <typeindex>
#include <cstddef>

namespace Hi_Engine
{
        // Consider replacing const ComponentRegistryEntry with optional, or raw ptr?

        struct ComponentRegistryEntry
        {
           std::string Name;
           std::size_t Size; // size in bytes
           std::size_t Alignment;
           ComponentID ID;

            // std::function<void(void*)> destructor;        
        };

        class ComponentRegistry
        {
        public:
            //template <ComponentType T, StringLike U>
            //void Register(U&& type);

            template <ComponentType T>
            void Register(std::string_view name);

            template <IsExactly<ComponentRegistryEntry> T>
            void Insert(T&& entry, std::string_view name);

            template <ComponentType T>
            [[nodiscard]] bool IsRegistered() const;

            [[nodiscard]] bool IsRegistered(ComponentID id) const;
      
            template <ComponentType T>
            [[nodiscard]] const ComponentRegistryEntry& GetComponentRegistryEntry() const;

            [[nodiscard]] const ComponentRegistryEntry& GetComponentRegistryEntry(ComponentID id) const;
      
            [[nodiscard]] const ComponentRegistryEntry& GetComponentRegistryEntry(const char* name) const; // replace with get component id from stirng?

            //template <ComponentType T>
            //[[nodiscard]] ComponentID GetComponentID() const noexcept;

            void Clear();
    
        private:
            //[[nodiscard]] ComponentID GenerateID() const noexcept;

            std::unordered_map<ComponentID, ComponentRegistryEntry> m_idToComponentData; // store in array instead?

            std::unordered_map<std::type_index, ComponentRegistryEntry*> m_typeToComponentData;
            std::unordered_map<std::string, ComponentRegistryEntry*> m_nameToComponentData;
        };

    #pragma region Templated_Methods
    
        template<ComponentType T>
        void ComponentRegistry::Register(std::string_view name)
        {
            auto id = GetComponentID<T>();

            ComponentRegistryEntry entry
            {
                name,
                sizeof(T),
                alignof(T),
                id
                // [](void* ptr) { static_cast<T*>(ptr)->~T(); }
            };

            const auto& [it, success] = m_idToComponentData.insert({ id, std::move(entry) });

            if (success)
            {
                std::type_index type = typeid(T);

                m_typeToComponentData.insert({ type, &it->second });
                m_nameToComponentData.insert({ name, &it->second });
            }
            else
            {
                Logger::LogWarning("[ComponentRegistry::RegisterComponent] - Failed to insert component type");
            }
        }

        template <IsExactly<ComponentRegistryEntry> T>
        void ComponentRegistry::Insert(T&& entry, std::string_view name)
        {
            const auto& [it, success] = m_idToComponentData.insert(GetComponentID<T>(), std::forward<T>(entry));

            if (success)
            {
                m_typeToComponentData.insert({ std::type_index(typeid(T)), &it->second });
                m_nameToComponentData.insert({ name, &it->second });
            }
        }

        template <ComponentType T>
        bool ComponentRegistry::IsRegistered() const
        {
            return m_typeToComponentData.contains(std::type_index(typeid(T)));
        }

        template <ComponentType T>
        const ComponentRegistryEntry& ComponentRegistry::GetComponentRegistryEntry() const
        {  
            auto type = std::type_index(typeid(T));
            
            assert(m_typeToComponentData.contains(type) && "Id not found");
            return m_typeToComponentData.at(type);
        }

        //template <ComponentType T>
        //ComponentID Hi_Engine::ComponentRegistry::GetComponentID() const noexcept
        //{
        //    static const ComponentID id = GenerateID();
        //    return id;
        //}

    #pragma endregion
}