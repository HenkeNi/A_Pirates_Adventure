#pragma once
#include "../IService.h"

namespace Hi_Engine
{
	// TODO; improve this class...
	// AssetService
	template <class Resource, typename Identifier = std::string>
	class ResourceService : public IService
	{
	public:		

		[[nodiscard]] const Resource& Get(const Identifier& id) const;

		[[nodiscard]] Resource& Get(const Identifier& id);
		
		[[nodiscard]] std::shared_ptr<const Resource> TryGetShared(const Identifier& id) const;

		[[nodiscard]] std::shared_ptr<Resource> TryGetShared(const Identifier& id);

		[[nodiscard]] std::weak_ptr<const Resource> TryGetWeak(const Identifier& id) const;

		[[nodiscard]] std::weak_ptr<Resource> TryGetWeak(const Identifier& id);

		std::shared_ptr<Resource> GetResource(const Identifier& identifier);					// return pointer instead
		const std::shared_ptr<Resource>& GetResource(const Identifier& identifier) const;
		bool HasResource(const Identifier& identifier) const;

		//void LoadResources(const std::string& filePath);
		void Insert(Identifier identifier, std::shared_ptr<Resource> resource);
		void Clear();

	private:
		std::unordered_map<Identifier, std::shared_ptr<Resource>> m_resources;
	};

	/*using TextureHolder = ResourceHolder<Texture2D>;
	using ShaderHolder  = ResourceHolder<GLSLShader>;*/

#pragma region Method_Definitions

	template <class Resource, typename Identifier>
	const Resource& ResourceService<Resource, Identifier>::Get(const Identifier& id) const
	{
		return {};
		// TODO: insert return statement here
	}

	template <class Resource, typename Identifier>
	Resource& ResourceService<Resource, Identifier>::Get(const Identifier& id)
	{
		return {};
		// TODO: insert return statement here
	}

	template <class Resource, typename Identifier>
	std::shared_ptr<const Resource> ResourceService<Resource, Identifier>::TryGetShared(const Identifier& id) const
	{
		return std::shared_ptr<const Resource>();
	}

	template <class Resource, typename Identifier>
	std::shared_ptr<Resource> ResourceService<Resource, Identifier>::TryGetShared(const Identifier& id)
	{
		return std::shared_ptr<Resource>();
	}

	template <class Resource, typename Identifier>
	std::weak_ptr<const Resource> ResourceService<Resource, Identifier>::TryGetWeak(const Identifier& id) const
	{
		return std::weak_ptr<const Resource>();
	}

	template <class Resource, typename Identifier>
	std::weak_ptr<Resource> ResourceService<Resource, Identifier>::TryGetWeak(const Identifier& id)
	{
		return std::weak_ptr<Resource>();
	}

	template <class Resource, typename Identifier>
	std::shared_ptr<Resource> ResourceService<Resource, Identifier>::GetResource(const Identifier& identifier)
	{
		assert(HasResource(identifier) && "[ResourceHolder::GetResource] - Resource not found");
		return m_resources.find(identifier)->second;
	}

	template <class Resource, typename Identifier>
	const std::shared_ptr<Resource>& ResourceService<Resource, Identifier>::GetResource(const Identifier& identifier) const
	{
		assert(HasResource(identifier) && "[ResourceHolder::GetResource] - Resource not found");
		return m_resources.find(identifier)->second;
	}

	template <class Resource, typename Identifier>
	bool ResourceService<Resource, Identifier>::HasResource(const Identifier& identifier) const
	{
		auto found = m_resources.find(identifier);
		return found != m_resources.end();
	}

	//template <class Resource, typename Identifier>
	//void ResourceService<Resource, Identifier>::LoadResources(const std::string& filePath)
	//{
	//	std::ifstream ifs{ filePath };
	//	std::string content{ std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>() };

	//	::rapidjson::Document document;
	//	document.Parse(content.c_str());

	//	assert(!document.HasParseError() && "Failed to parse resource!");

	//	for (auto& value : document.GetArray())
	//	{
	//		auto resource = std::make_unique<Resource>();
	//		assert(resource && "Failed to create resource");
	//		resource->Init(value);

	//		std::string name = resource->GetName();
	//		Insert(name, std::move(resource));
	//	}
	//}

	template <class Resource, typename Identifier>
	void ResourceService<Resource, Identifier>::Insert(Identifier identifier, std::shared_ptr<Resource> resource)
	{
		auto inserted = m_resources.insert(std::make_pair(identifier, std::move(resource)));
		assert(inserted.second);
	}

	template <class Resource, typename Identifier>
	void ResourceService<Resource, Identifier>::Clear()
	{
		m_resources.clear(); // TODO; delete/unload resources (call function)?
	}

#pragma endregion Method_Definitions
}