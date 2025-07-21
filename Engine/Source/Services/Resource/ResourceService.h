#pragma once
#include "../IService.h"

namespace Hi_Engine
{
	// TODO; improve this class...
	// AssetService
	template <typename ID, typename Res>
	class ResourceService : public IService
	{
	public:		
		template <typename... Args>
		Res& Emplace(ID id, Args&&... args);

		void Insert(ID id, std::shared_ptr<Res> resource);

		[[nodiscard]] const Res& Get(const ID& id) const;

		[[nodiscard]] Res& Get(const ID& id);
		
		[[nodiscard]] std::shared_ptr<const Res> TryGetShared(const ID& id) const;

		[[nodiscard]] std::shared_ptr<Res> TryGetShared(const ID& id);

		[[nodiscard]] std::weak_ptr<const Res> TryGetWeak(const ID& id) const;

		[[nodiscard]] std::weak_ptr<Res> TryGetWeak(const ID& id);

		[[nodiscard]] std::shared_ptr<Res> GetResource(const ID& id);					// return pointer instead
		[[nodiscard]] const std::shared_ptr<Res>& GetResource(const ID& id) const;
		
		[[nodiscard]] bool Contains(const ID& id) const; // rename Contains?

		//void LoadResources(const std::string& filePath);
		void Clear();

	private:
		std::unordered_map<ID, std::shared_ptr<Res>> m_resources;
	};

#pragma region Templated_Methods

	template <typename ID, typename Res>
	template <typename ...Args>
	Res& ResourceService<ID, Res>::Emplace(ID id, Args&&... args)
	{
		assert(!Contains(id) && "Resource already exist!");

		auto [it, success] = m_resources.insert({ id, std::make_shared<Res>(std::forward<Args>(args)...) });

		if (success)
		{
			return it->second;
		}

		throw std::runtime_error("Failed to create resource!");
		return Res{};
	}

	template <typename ID, typename Res>
	void ResourceService<ID, Res>::Insert(ID id, std::shared_ptr<Res> resource)
	{
		auto inserted = m_resources.insert(std::make_pair(id, std::move(resource)));
		assert(inserted.second);
	}

	template <typename ID, typename Res>
	const Res& ResourceService<ID, Res>::Get(const ID& id) const
	{
		//assert(Contains(id) && "Resource not found!");

		if (auto it = m_resources.find(id); it != m_resources.end())
		{
			return *it->second;
		}

		assert(false && "Resource not found!");
		return {};
	}

	template <typename ID, typename Res>
	Res& ResourceService<ID, Res>::Get(const ID& id)
	{
		return {};
		// TODO: insert return statement here
	}

	template <typename ID, typename Res>
	std::shared_ptr<const Res> ResourceService<ID, Res>::TryGetShared(const ID& id) const
	{
		return std::shared_ptr<const Res>();
	}

	template <typename ID, typename Res>
	std::shared_ptr<Res> ResourceService<ID, Res>::TryGetShared(const ID& id)
	{
		return std::shared_ptr<Res>();
	}

	template <typename ID, typename Res>
	std::weak_ptr<const Res> ResourceService<ID, Res>::TryGetWeak(const ID& id) const
	{
		return std::weak_ptr<const Res>();
	}

	template <typename ID, typename Res>
	std::weak_ptr<Res> ResourceService<ID, Res>::TryGetWeak(const ID& id)
	{
		return std::weak_ptr<Res>();
	}

	template <typename ID, typename Res>
	std::shared_ptr<Res> ResourceService<ID, Res>::GetResource(const ID& id)
	{
		assert(Contains(id) && "[ResourceHolder::GetResource] - Resource not found");
		return m_resources.find(id)->second;
	}

	template <typename ID, typename Res>
	const std::shared_ptr<Res>& ResourceService<ID, Res>::GetResource(const ID& id) const
	{
		assert(Contains(id) && "[ResourceHolder::GetResource] - Resource not found");
		return m_resources.find(id)->second;
	}

	template <typename ID, typename Res>
	bool ResourceService<ID, Res>::Contains(const ID& id) const
	{
		auto found = m_resources.find(id);
		return found != m_resources.end();
	}

	template <typename ID, typename Res>
	void ResourceService<ID, Res>::Clear()
	{
		m_resources.clear(); // TODO; delete/unload resources (call function)?
	}

#pragma endregion
}