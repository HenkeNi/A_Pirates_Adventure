#pragma once
#include <../../../ThirdParty/GLEW/include/GL/glew.h> // use typedef for GLEnum?

namespace Hi_Engine
{
	using namespace Math;

	class Texture2D
	{
	public:
		Texture2D(GLenum textureFormat = GL_RGB, bool linearFiltering = true);
		~Texture2D();

		void			Init(const IVector2& size, unsigned char* data);		// Take in texturedata...
		// Delte function??
		void			Bind()												const;
		void			Unbind()											const;

		const IVector2& GetSize()											const;
		unsigned		GetID()												const;
		unsigned char*	GetData()											const;

	private:
		IVector2		m_size;
		GLenum			m_internalFormat, m_imageFormat;
		unsigned		m_id;

		unsigned char*	m_data;
		bool			m_linearFiltering;	// replace with GLInt?? 
	};
}