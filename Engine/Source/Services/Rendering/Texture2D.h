#pragma once
//#include <Dependencies/GLEW/include/GL/glew.h>

//#include <../rapidjson.h>
#include <../Dependencies/rapidjson/document.h>

typedef unsigned int GLenum;

namespace Hi_Engine
{
	using namespace Math;

	// TODO; Create a texture loader class that loads the actual data? (static)

	/*class Texture2DNew
	{
	public:

	private:
	};*/


	class Texture2D
	{
	public:
		Texture2D(); 
		~Texture2D();

		static std::optional<Texture2D> FromJSON(const rapidjson::Value& json);

		void			Init(const std::string& name, const std::string& path, const std::string& filtering); // TODO , use construtor instead! or FromJson
		//void			Init(const rapidjson::Value& value);
		void			Create(const IVector2& size, GLenum format, bool linear, unsigned char* data);		// Take in texturedata...
		// Delte function??
		void			Bind()												const;
		void			Unbind()											const;
	
		const IVector2& GetSize()											const;
		unsigned		GetID()												const;
		unsigned char*	GetData()											const;
		inline const std::string& GetName() const { return m_name; }

	private:
		std::string m_name;
		IVector2 m_size;
		unsigned char* m_data;
		unsigned m_id;
	};
}