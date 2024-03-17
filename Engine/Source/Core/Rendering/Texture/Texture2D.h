#pragma once
#include <../../../ThirdParty/GLEW/include/GL/glew.h>

namespace Hi_Engine
{
	namespace CU = CommonUtilities;

	class Texture2D
	{
	public:
		Texture2D(GLenum textureFormat = GL_RGB, bool linearFiltering = true);
		~Texture2D();

		void					Init(const CU::Vector2<int>& size, unsigned char* data);		// Take in texturedata...
		void					Bind()																const;
		void					Unbind()															const;

		const CU::Vector2<int>& GetSize()															const;
		unsigned				GetID()																const;
		unsigned char*			GetData()															const;

	private:
		CU::Vector2<int>		m_size;
		GLenum					m_internalFormat, m_imageFormat;
		unsigned				m_id;

		unsigned char* m_data;
		bool m_linearFiltering;	// replace with GLInt?? 
	};
}