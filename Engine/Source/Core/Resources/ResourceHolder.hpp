#pragma once
//#include "Math/Vectors/Vector.hpp"
#include "Core/Rendering/Shader/Shader.h"
#include "Core/Rendering/Texture/Texture2D.h"
//#include "Rendering/Shader/Shader.h"
//#include "Rendering/Texture/Texture2D.h"
#include <document.h>
#include <memory>
#include <string>
#include <unordered_map>
#include <stb_image.h>
#include <fstream>

// TODO; rename ResourceManager? 

namespace Hi_Engine
{
	template <class Resource, typename Identifier = std::string>
	class ResourceHolder
	{
	public:
		ResourceHolder(const ResourceHolder&)			 = delete;
		ResourceHolder& operator=(const ResourceHolder&) = delete;

		static ResourceHolder&	GetInstance();
		Resource&				GetResource(const Identifier& anID);
		const Resource&			GetResource(const Identifier& anID)		const;
		bool					HasComponent(const Identifier& anID)		const;

		void					FetchAll(const std::string& aFilePath);
		void					Insert(Identifier anID, std::unique_ptr<Resource> aResource);
		void					Load(const Identifier& anID, const std::string& aPath, bool alpha);
		void					Load(const Identifier& anID, const std::string& aPath);
		void					Clear();

	private:
		ResourceHolder();

		std::unordered_map<Identifier, std::unique_ptr<Resource>> m_resources;
	};

	/*using TextureHolder = ResourceHolder<Texture2D>;
	using ShaderHolder  = ResourceHolder<Shader>;*/

#pragma region Constructor

	template <class Resource, typename Identifier>
	ResourceHolder<Resource, Identifier>::ResourceHolder()
	{
	}

#pragma endregion Constructor

#pragma region Method_Definitions

	template <class Resource, typename Identifier>
	ResourceHolder<Resource, Identifier>& ResourceHolder<Resource, Identifier>::GetInstance()
	{
		static ResourceHolder instance;
		return instance;
	}

	template <class Resource, typename Identifier>
	Resource& ResourceHolder<Resource, Identifier>::GetResource(const Identifier& anID)
	{
		assert(HasComponent(anID));
		return *m_resources.find(anID)->second;
	}

	template <class Resource, typename Identifier>
	const Resource& ResourceHolder<Resource, Identifier>::GetResource(const Identifier& anID) const
	{
		return GetResource(anID);
	}

	template <class Resource, typename Identifier>
	bool ResourceHolder<Resource, Identifier>::HasComponent(const Identifier& anID) const
	{
		auto found = m_resources.find(anID);
		return found != m_resources.end();
	}

	template <class Resource, typename Identifier>
	void ResourceHolder<Resource, Identifier>::FetchAll(const std::string& aFilePath)
	{
		std::ifstream ifs{ aFilePath };
		std::string content{ std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>() };

		rapidjson::Document document;
		if (document.Parse(content.c_str()).HasParseError())
		{
			std::cerr << "[Parse Error]: " << aFilePath << '\n'; 
			return;
		}

		for (auto& value : document.GetArray())
		{
			auto name = value["name"].GetString();
			auto path = value["filepath"].GetString();

			value.HasMember("alpha") ? Load(name, path, value["alpha"].GetBool()) : Load(name, path);
		}
	}

	template <class Resource, typename Identifier>
	void ResourceHolder<Resource, Identifier>::Insert(Identifier anID, std::unique_ptr<Resource> aResource)
	{
		auto inserted = m_resources.insert(std::make_pair(anID, std::move(aResource)));
		assert(inserted.second);
	}

	template <class Resource, typename Identifier>
	void ResourceHolder<Resource, Identifier>::Load(const Identifier& anID, const std::string& aPath, bool alpha)
	{
		assert(false && "*** No Function Overload Found! ***");
	}
	
	template <class Resource, typename Identifier>
	void ResourceHolder<Resource, Identifier>::Load(const Identifier& anID, const std::string& aPath)
	{
		assert(false && "*** No Function Overload Found! ***");
	}

	template <>
	inline void ResourceHolder<Texture2D, std::string>::Load(const std::string& aResourceName, const std::string& aPath, bool alpha)
	{
		auto texture = std::make_unique<Texture2D>(alpha);

		int width, height, nrChannels;
		unsigned char* data = stbi_load(aPath.c_str(), &width, &height, &nrChannels, 0);

		texture->Init({ width, height }, data);
		stbi_image_free(data);

		Insert(aResourceName, std::move(texture));
	}

	template <>
	inline void ResourceHolder<Shader, std::string>::Load(const std::string& aResourceName, const std::string& aPath)
	{
		auto shader = std::make_unique<Shader>();

		std::string vertex, fragment;

		std::ifstream vertexStream{ aPath + aResourceName + ".vertex.glsl" };
		vertex = { std::istreambuf_iterator<char>(vertexStream), std::istreambuf_iterator<char>() };

		std::ifstream fragmentStream{ aPath + aResourceName + ".fragment.glsl" };
		fragment = { std::istreambuf_iterator<char>(fragmentStream), std::istreambuf_iterator<char>() };

		// TODO: Geometryshader

		shader->Init(vertex.c_str(), fragment.c_str(), nullptr);

		Insert(aResourceName, std::move(shader));
	}

	template <class Resource, typename Identifier>
	void ResourceHolder<Resource, Identifier>::Clear()
	{
		m_resources.clear();
	}

#pragma endregion Method_Definitions
}