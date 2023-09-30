#pragma once
#include <../../../ThirdParty/GLEW/include/GL/glew.h>

namespace Hi_Engine
{
	namespace CU = CommonUtilities;

	class Texture2D
	{
	public:
		Texture2D(GLenum aTextureFormat = GL_RGB, bool aLinearFiltering = true);
		~Texture2D();

		void					Init(const CU::Vector2<int>& aSize, unsigned char* someData);		// Take in texturedata...
		void					Bind()																const;
		void					Unbind()															const;

		const CU::Vector2<int>& GetSize()															const;
		unsigned				GetID()																const;

	private:
		CU::Vector2<int>		m_size;
		GLenum					m_internalFormat, m_imageFormat;
		unsigned				m_id;

		bool m_linearFiltering;
	};
}