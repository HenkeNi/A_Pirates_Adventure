#pragma once
#include "../../../Utility/Math/Vectors/Vector.hpp"

namespace Hi_Engine
{
	namespace CU = CommonUtilities;

	class Shader;
	class Texture2D;
	//class Subtexture2D;

	class Material
	{
	public:
		Material();
		//Material(Subtexture2D* aSubtexture, Shader* aShader);
		Material(Texture2D* texture, Shader* shader);

		void						SetColor(const CU::Vector4<float> color);
		//void						SetSubtexture(const Subtexture2D* aSubtexture);
		void						SetTexture(const Texture2D* texture);
		void						SetShader(Shader* shader);

		const CU::Vector4<float>&	GetColor()		const;
		//const Subtexture2D*			GetSubtexture()	const;
		const Texture2D*			GetTexture()	const;
		const Shader*				GetShader()		const;

	private:
		CU::Vector4<float>			m_color;
		//const Subtexture2D*			m_subtexture;
		const Texture2D*			m_texture; 
		const Shader*				m_shader;
	};
}