#pragma once
//#include <Dependencies/GLEW/include/GL/glew.h>

typedef unsigned int GLenum;

namespace Hi_Engine
{
	using namespace Math;

	class Texture2D
	{
	public:
		Texture2D();
		~Texture2D();

		void			Init(const rapidjson::Value& value);
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