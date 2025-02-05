#pragma once
#include <typeindex>
#include <memory> // REMOVE LATER

// Send module loaded / unloaded events
// load modules doesnt load modules?? needs to register still?

namespace Hi_Engine
{
	class Module;

	class ModuleManager
	{
	public:
		ModuleManager();
		~ModuleManager();

		bool Init();
		void Shutdown();

		template <typename T, typename... Args>
		void RegisterModule(Args&&... args);

		template <typename T>
		void AddModule(const std::shared_ptr<T>& module);

		template <typename T>
		void RemoveModule();

		template <typename T>
		std::weak_ptr<T> GetModule();
		
		// For each function?
		void LoadModules();

	private:
		std::unordered_map<std::type_index, std::shared_ptr<Module>> m_modules;
	};

#pragma region Method_Definitions

	template <typename T, typename... Args>
	inline void ModuleManager::RegisterModule(Args&&... args)
	{
		auto typeIndex = std::type_index(typeid(T));
		m_modules.insert(std::make_pair(typeIndex, std::make_shared<T>(*this, std::forward<Args>(args)...)));
	}

	template<typename T>
	inline void ModuleManager::AddModule(const std::shared_ptr<T>& module)
	{
		auto typeIndex = std::type_index(typeid(T));
		m_modules.insert(std::make_pair(typeIndex, module));
	}

	template<typename T>
	inline void ModuleManager::RemoveModule()
	{
		auto typeIndex = std::type_index(typeid(T));
		m_modules.erase(typeIndex);
	}

	template<typename T>
	inline std::weak_ptr<T> ModuleManager::GetModule()
	{
		auto typeIndex = std::type_index(typeid(T));
		auto it = m_modules.find(typeIndex);

		if (it != m_modules.end())
		{
			return dynamic_pointer_cast<T>(it->second);
		}

		return std::weak_ptr<T>();
	}

#pragma endregion Method_Definitions
}
