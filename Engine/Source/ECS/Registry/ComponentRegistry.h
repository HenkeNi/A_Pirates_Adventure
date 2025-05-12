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

    //using ComponentRegistry = std::unordered_map<std::string, struct ComponentRegistryEntry>; // make into class?

//struct ComponentRegistryEntry
//{
//	std::function<void(Entity)> AddComponent;
//	std::function<void(Entity, const ComponentProperties&)> InitializeComponent;
//};

    struct CallbackRegistry // TODO; fix!
    {
        //inline static std::unordered_map<const char*, std::function<void(Entity)>> Callbacks; // Maybe in Timer/Button Component (or system), or separate Callback/Action component?
    };


	// singelton or all static?
    class ComponentRegistry
    {
    public:
        using Signatures = std::unordered_map<std::string, Signature>; // or store in ECSTypes?

        template <ComponentType T>
        void RegisterComponent(const char* name);

        //template <ComponentType T>  //template <ComponentType T, StringConvertible U>
        //void RegisterComponent(auto&& name); // TODO; add type safety for auto? static function in registry class instead?
        //{
        //    m_componentRegistry.RegisterComponent<T>(std::forward<decltype(name)>(name));

        //    // store serilization data as well? initialization data?

        //    //ComponentRegistryEntry entry;
        //    //entry.AddComponent = [this](Entity entity)
        //    //{
        //    //	AddComponents<T>(entity);
        //    //};
        //    //entry.InitializeComponent = [this](Entity entity, const ComponentProperties& properties)
        //    //{
        //    //	if (auto* component = m_componentManager.GetComponent<T>(entity))
        //    //		InitializeComponent(component, properties);
        //    //};
        //}

        template <ComponentType T>
        bool IsRegistered() const;

        template <ComponentType... Ts>
        Signatures GetSignatures() const
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

        std::unordered_map<std::type_index, ComponentData> m_typeToComponentData; // sparse set? is type idnex an intgeer?
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
   
    template <ComponentType T>
    bool ComponentRegistry::IsRegistered() const
    {
        return m_typeToComponentData.find(typeid(T)) != m_typeToComponentData.end();
    }

#pragma endregion
}