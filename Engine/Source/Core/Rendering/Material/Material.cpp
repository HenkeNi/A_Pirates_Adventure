#include "Pch.h"
#include "Material.h"
#include "../Shader/Shader.h"
#include "../Texture/Texture2D.h"


namespace Hi_Engine
{
	Material::Material()
		: Material{ nullptr, nullptr }
	{
	}

	//Material::Material(Subtexture2D* aSubtexture, Shader* aShader)
	//	: m_subtexture{ aSubtexture }, m_shader{ aShader }, m_color{ 1.f, 1.f, 1.f, 1.f }
	//{
	//}

	Material::Material(Texture2D* texture, Shader* shader)
		: m_texture{ texture }, m_shader{ shader }, m_color{ 1.f, 1.f, 1.f, 1.f }
	{
	}

	void Material::SetColor(const CU::Vector4<float> color)
	{
		m_color = color;
	}

	//void Material::SetSubtexture(const Subtexture2D* aSubtexture)
	//{
	//	m_subtexture = aSubtexture;
	//}

	void Material::SetTexture(const Texture2D* texture)
	{
		m_texture = texture;
	}

	void Material::SetShader(Shader* shader)
	{
		m_shader = shader;
	}

	const CU::Vector4<float>& Material::GetColor() const
	{
		return m_color;
	}

	/*const Subtexture2D* Material::GetSubtexture()	const
	{
		return m_subtexture;
	}*/

	const Texture2D* Material::GetTexture() const
	{
		return m_texture;
	}

	const Shader* Material::GetShader() const
	{
		return m_shader;
	}
}