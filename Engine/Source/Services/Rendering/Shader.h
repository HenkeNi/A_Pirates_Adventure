#pragma once
//#include <Dependencies/GLEW/include/GL/glew.h>

// FIX::
//#include <../../ThirdParty/GLEW/include/GL/glew.h>
// #include <../../ThirdParty/glm/glm.hpp>
#include <../Dependencies/rapidjson/document.h>

// enum class GLenum;

typedef unsigned int GLenum;

namespace Hi_Engine
{
	using namespace Math;


	class GLSLShader
	{
	public:
		GLSLShader();
		~GLSLShader();

		void Init(const rapidjson::Value& value);
		const GLSLShader& Activate() const;	// make const? => change shader in material to const pointer.?!
		
		inline const std::string& GetName() const { return m_name; }


		void Create(const char* vSource, const char* fSource, const char* gSource);
		void SetBool(const std::string& name, bool value)							const;
		void SetInt(const std::string& name, int value)								const;
		void SetFloat(const std::string& name, float value)							const;
		void SetIntArray(const std::string& name, int* values, int count)			const;
		void SetVector2f(const std::string& name, const FVector2& value)			const;
		void SetVector3f(const std::string& name, const FVector3& value)			const;
		void SetVector4f(const std::string& name, const FVector4& value)			const;
		void SetMatrix4(const std::string& name, const glm::mat4& matrix)			const;

	private:
		int	 CreateShader(GLenum shaderType, const char* source);
		void CheckCompileErrors(unsigned object, const std::string& type);

		std::string m_name;
		unsigned m_id;
	};
}