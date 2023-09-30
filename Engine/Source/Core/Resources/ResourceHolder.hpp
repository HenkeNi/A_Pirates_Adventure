#pragma once
//#include "Math/Vectors/Vector.hpp"
#include "Core/Rendering/Shader/Shader.h"
#include "Core/Rendering/Texture/Texture2D.h"
#include "Core/Rendering/Texture/Subtexture2D.h"

#include "Core/Rendering/Font/Font.h"
#include <../../ThirdParty/rapidjson/document.h>
// #include <document.h>
#include <memory>
#include <string>
#include <unordered_map>
#include <../../ThirdParty/stb_image/stb_image.h>
#include <fstream>
#include <iostream>

#include <../../ThirdParty/FreeType/include/ft2build.h>
//#include <ft2build.h>
#include FT_FREETYPE_H  

// TODO; rename ResourceManager? 

// Todo, use inheritance instead? For loading, etcc..?

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
		bool					HasComponent(const Identifier& anID)	const;

		void					FetchAll(const std::string& aFilePath);
		void					Insert(Identifier anID, std::unique_ptr<Resource> aResource);

		void					Load(const rapidjson::Document& aDocument);
		//void					Load(const rapidjson::Value& aValue);
		//void					Load(const rapidjson::GenericValue<rapidjson::UTF8<>>& aValue);

		//void					Load(const Identifier& anID, const std::string& aPath, bool alpha);	// Perfect forwarding posible? take in GLenum instead!
		//void					Load(const Identifier& anID, const std::string& aPath);
		//void					Load(const Identifier& anID, const std::string& aPath, int aSize);	// rename aSize to aFontSize?
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
		document.Parse(content.c_str());

		assert(!document.HasParseError() && "Failed to parse resource!");

		Load(document);

		//for (auto& value : document.GetArray())
		//{
		//	Load(std::move(value));

		//	//auto name = value["name"].GetString();
		//	//auto path = value["filepath"].GetString();

		//	//if (value.HasMember("alpha"))
		//	//	Load(name, path, value["alpha"].GetBool());
		//	//else if (value.HasMember("size"))
		//	//	Load(name, path, value["size"].GetInt());
		//	//else
		//	//	Load(name, path);
		//}
	}

	template <class Resource, typename Identifier>
	void ResourceHolder<Resource, Identifier>::Insert(Identifier anID, std::unique_ptr<Resource> aResource)
	{
		auto inserted = m_resources.insert(std::make_pair(anID, std::move(aResource)));
		assert(inserted.second);
	}


	// TODO; Create templated Load version for each that takes in a



	template <class Resource, typename Identifier>
	inline void	ResourceHolder<Resource, Identifier>::Load(const rapidjson::Document& aDocument)
	{
		assert(false);
	}

	template <>
	inline void	ResourceHolder<Texture2D, std::string>::Load(const rapidjson::Document& aDocument)
	{
		for (auto& value : aDocument.GetArray())
		{
			std::string id = value["id"].GetString();
			std::string path = value["path"].GetString();
			std::string filtering = value["filtering"].GetString();
			bool alpha = value["alpha"].GetBool();

			// width, height??

			stbi_set_flip_vertically_on_load(true);

			auto texture = std::make_unique<Texture2D>(alpha ? GL_RGBA : GL_RGB, filtering == "Linear");

			int width, height, nrChannels;
			unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

			texture->Init({ width, height }, data);
			stbi_image_free(data);

			Insert(id, std::move(texture));
		
		
			// TODO; use static function
			// CREATE subtextures... 
			//int textureWidth = value["width"].GetInt();
			//int textureHeight = value["height"].GetInt();

			int rows = value["rows"].GetInt();
			int cols = value["cols"].GetInt();

			int spriteWidth = (float)width / cols;
			int spriteHeight = (float)height / rows;


			for (float row = 0; row < rows; ++row)
			{
				for (float col = 0; col < cols; ++col)
				{
					float minX = (col * spriteWidth) / width;
					float minY = (row * spriteHeight) / height;
					float maxX = ((col + 1) * spriteWidth) / width;
					float maxY = ((row + 1) * spriteHeight) / height;


					//int minX = (float)(col) / cols;
					//int minY = (float)(row) / rows;
					//int maxX = (float)(col + 1) / cols;
					//int maxY = (float)(row + 1) / rows;

					auto subtexture = std::make_unique<Subtexture2D>(GetResource(id), glm::vec2{ minX, minY }, glm::vec2{ maxX, maxY });

					std::string subID = id + "_" + std::to_string((int)row) + std::to_string((int)col);
					ResourceHolder<Subtexture2D>::GetInstance().Insert(subID, std::move(subtexture));
				}
			}

			int x = 10;
			x += 10;
		}
	}

	template <>
	inline void	ResourceHolder<Subtexture2D, std::string>::Load(const rapidjson::Document& aDocument)
	{
		for (auto& value : aDocument.GetArray())
		{
			std::string parent = value["parent_id"].GetString();
			auto& parentTexture = ResourceHolder<Texture2D>::GetInstance().GetResource(parent);

			float minX = value["min_uv"][0].GetFloat();
			float minY = value["min_uv"][1].GetFloat();

			float maxX = value["max_uv"][0].GetFloat();
			float maxY = value["max_uv"][1].GetFloat();

			auto subtexture = std::make_unique<Subtexture2D>(parentTexture, glm::vec2{ minX, minY }, glm::vec2{ maxX, maxY });

			std::string id = value["id"].GetString();

			Insert(id, std::move(subtexture));
		}
	}

	template <>
	inline void	ResourceHolder<Shader, std::string>::Load(const rapidjson::Document& aDocument)
	{
		for (auto& value : aDocument.GetArray())
		{
			std::string id = value["name"].GetString();
			std::string path = value["filepath"].GetString();

			auto shader = std::make_unique<Shader>();

			std::string vertex, fragment;

			std::ifstream vertexStream{ path + id + ".vertex.glsl" };
			vertex = { std::istreambuf_iterator<char>(vertexStream), std::istreambuf_iterator<char>() };

			std::ifstream fragmentStream{ path + id + ".fragment.glsl" };
			fragment = { std::istreambuf_iterator<char>(fragmentStream), std::istreambuf_iterator<char>() };

			// TODO: Geometryshader

			shader->Init(vertex.c_str(), fragment.c_str(), nullptr);

			Insert(id, std::move(shader));
		}
	}

	template <>
	inline void	ResourceHolder<Font, std::string>::Load(const rapidjson::Document& aDocument)
	{
		for (auto& value : aDocument.GetArray())
		{
			std::string id = value["name"].GetString();
			std::string path = value["filepath"].GetString();
			std::string name = value["name"].GetString();

			int size = value["size"].GetInt();

			auto font = std::make_unique<Font>();

			// Initialize (and load) the FreeType library			- need to do every time?
			FT_Library ft;
			if (FT_Init_FreeType(&ft))
				assert(false && "ERROR: Could not init FreeType Library");

			// Load font as face
			FT_Face face;
			if (FT_New_Face(ft, path.c_str(), 0, &face))
				assert(false && "ERROR: Failed to load font");

			// Set size to load glyphs as
			FT_Set_Pixel_Sizes(face, 0, size);

			// Disable byte-alignment restriction
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

			const auto& glyph = face->glyph;

			// Compile, and store, the first 128 ASCII characters
			for (unsigned char c = 0; c < 128; ++c)
			{
				// Load character glyph 
				if (FT_Load_Char(face, c, FT_LOAD_RENDER))
				{
					std::cout << "ERROR: Failed to load Glyph\n";
					continue;
				}

				std::string identifier = name + "_" + std::to_string(c);
				ResourceHolder<Texture2D>::GetInstance().Insert(identifier, std::make_unique<Texture2D>(GL_RED));
				ResourceHolder<Texture2D>::GetInstance().GetResource(identifier)
					.Init({ (int)glyph->bitmap.width, (int)glyph->bitmap.rows }, glyph->bitmap.buffer);

				Character character;
				character.m_size = { glyph->bitmap.width, glyph->bitmap.rows };
				character.m_bearing = { (int)glyph->bitmap_left, (int)glyph->bitmap_top };
				character.m_textureID = identifier;
				character.m_advance = glyph->advance.x;

				font->AddCharacter(c, std::move(character));
			}

			glBindTexture(GL_TEXTURE_2D, 0);

			// destroy FreeType once we're finished
			FT_Done_Face(face);
			FT_Done_FreeType(ft);

			Insert(name, std::move(font));
		}
	}




	//template <class Resource, typename Identifier>
	//void ResourceHolder<Resource, Identifier>::Load(const Identifier& anID, const std::string& aPath, bool alpha)
	//{
	//	assert(false && "*** No Function Overload Found! ***");
	//}
	//
	//template <class Resource, typename Identifier>
	//void ResourceHolder<Resource, Identifier>::Load(const Identifier& anID, const std::string& aPath)
	//{
	//	assert(false && "*** No Function Overload Found! ***");
	//}
	//
	//template <class Resource, typename Identifier>
	//void ResourceHolder<Resource, Identifier>::Load(const Identifier& anID, const std::string& aPath, int aSize)
	//{
	//	assert(false && "*** No Function Overload Found! ***");
	//}

	//template <>
	//inline void ResourceHolder<Texture2D, std::string>::Load(const std::string& aResourceName, const std::string& aPath, bool alpha)
	//{
	//	stbi_set_flip_vertically_on_load(true);

	//	auto texture = std::make_unique<Texture2D>(alpha ? GL_RGBA : GL_RGB);

	//	int width, height, nrChannels;
	//	unsigned char* data = stbi_load(aPath.c_str(), &width, &height, &nrChannels, 0);

	//	texture->Init({ width, height }, data);
	//	stbi_image_free(data);

	//	Insert(aResourceName, std::move(texture));
	//}

	//template <>
	//inline void ResourceHolder<Shader, std::string>::Load(const std::string& aResourceName, const std::string& aPath)
	//{
	//	auto shader = std::make_unique<Shader>();

	//	std::string vertex, fragment;

	//	std::ifstream vertexStream{ aPath + aResourceName + ".vertex.glsl" };
	//	vertex = { std::istreambuf_iterator<char>(vertexStream), std::istreambuf_iterator<char>() };

	//	std::ifstream fragmentStream{ aPath + aResourceName + ".fragment.glsl" };
	//	fragment = { std::istreambuf_iterator<char>(fragmentStream), std::istreambuf_iterator<char>() };

	//	// TODO: Geometryshader

	//	shader->Init(vertex.c_str(), fragment.c_str(), nullptr);

	//	Insert(aResourceName, std::move(shader));
	//}

	//template <>
	//inline void ResourceHolder<Font, std::string>::Load(const std::string& aResourceName, const std::string& aPath, int aSize)
	//{
	//	auto font = std::make_unique<Font>();
	//	
	//	// Initialize (and load) the FreeType library			- need to do every time?
	//	FT_Library ft;
	//	if (FT_Init_FreeType(&ft))
	//		assert(false && "ERROR: Could not init FreeType Library");

	//	// Load font as face
	//	FT_Face face;
	//	if (FT_New_Face(ft, aPath.c_str(), 0, &face))
	//		assert(false && "ERROR: Failed to load font");

	//	// Set size to load glyphs as
	//	FT_Set_Pixel_Sizes(face, 0, aSize);
	//	
	//	// Disable byte-alignment restriction
	//	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	//	const auto& glyph = face->glyph;

	//	// Compile, and store, the first 128 ASCII characters
	//	for (unsigned char c = 0; c < 128; ++c)
	//	{
	//		// Load character glyph 
	//		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
	//		{
	//			std::cout << "ERROR: Failed to load Glyph\n";
	//			continue;
	//		}

	//		std::string identifier = aResourceName + "_" + std::to_string(c);
	//		ResourceHolder<Texture2D>::GetInstance().Insert(identifier, std::make_unique<Texture2D>(GL_RED));
	//		ResourceHolder<Texture2D>::GetInstance().GetResource(identifier)
	//			.Init({ (int)glyph->bitmap.width, (int)glyph->bitmap.rows }, glyph->bitmap.buffer);
	//		
	//		Character character;
	//		character.m_size = { glyph->bitmap.width, glyph->bitmap.rows };
	//		character.m_bearing = { (int)glyph->bitmap_left, (int)glyph->bitmap_top };
	//		character.m_textureID = identifier;
	//		character.m_advance = glyph->advance.x;
	//		
	//		font->AddCharacter(c, std::move(character));
	//	}

	//	glBindTexture(GL_TEXTURE_2D, 0);

	//	// destroy FreeType once we're finished
	//	FT_Done_Face(face);
	//	FT_Done_FreeType(ft);

	//	Insert(aResourceName, std::move(font));
	//}

	template <class Resource, typename Identifier>
	void ResourceHolder<Resource, Identifier>::Clear()
	{
		m_resources.clear();
	}

#pragma endregion Method_Definitions
}