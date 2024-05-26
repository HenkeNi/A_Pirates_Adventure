#pragma once
//#include "../../../Utility/Math/Vectors/Vector.hpp"

namespace Hi_Engine
{
	using namespace Math;

	class GLSLShader;
	class Texture2D;
	//class Subtexture2D;

	class Material // TODO; delete?
	{
	public:
		Material();
		//Material(Subtexture2D* aSubtexture, GLSLShader* aShader);
		Material(Texture2D* texture, GLSLShader* shader);

		void						SetColor(const FVector4& color);
		//void						SetSubtexture(const Subtexture2D* aSubtexture);
		void						SetTexture(const Texture2D* texture);
		void						SetShader(GLSLShader* shader);

		const FVector4&	GetColor()		const;
		//const Subtexture2D*			GetSubtexture()	const;
		const Texture2D*				GetTexture()	const;
		const GLSLShader*				GetShader()		const;

	private:
		FVector4			m_color;
		//const Subtexture2D*			m_subtexture;
		const Texture2D*			m_texture; 
		const GLSLShader*				m_shader;
	};
}