#include "Pch.h"
#include "Shader.h"
#include "../Data/Structs.h"


namespace Hi_Engine
{
    Shader::Shader()
        : m_id{ 0 }
    {
    }

    Shader::~Shader()
    {
        glDeleteProgram(m_id);
    }

    const Shader& Shader::Activate() const
    {
        glUseProgram(m_id);
        return *this;
    }

    void Shader::Init(const char* vSource, const char* fSource, const char* gSource)
    {
        /* Create Vertex Shader */
        unsigned vertexShader = CreateShader(GL_VERTEX_SHADER, vSource);
        CheckCompileErrors(vertexShader, "VERTEX");

        /* Create Fragment Shader */
        unsigned fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fSource);
        CheckCompileErrors(fragmentShader, "FRAGMENT");

        /* Create Geometry Shader */
        unsigned geometryShader;
        if (gSource)
        {
            geometryShader = CreateShader(GL_GEOMETRY_SHADER, gSource);
            CheckCompileErrors(geometryShader, "GEOMETRY");
        }

        /* Create Program */
        m_id = glCreateProgram();
        glAttachShader(m_id, vertexShader);
        glAttachShader(m_id, fragmentShader);

        if (gSource)
            glAttachShader(m_id, geometryShader);

        /* Link Program */
        glLinkProgram(m_id);
        CheckCompileErrors(m_id, "PROGRAM");

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        if (gSource)
            glDeleteShader(geometryShader);
    }

    void Shader::SetBool(const std::string& name, bool value) const
    {
        glUniform1i(glGetUniformLocation(m_id, name.c_str()), (int)value);
    }

    void Shader::SetInt(const std::string& name, int value) const
    {
        glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
    }

    void Shader::SetFloat(const std::string& name, float value) const
    {
        glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
    }

    void Shader::SetIntArray(const std::string& name, int* values, int count) const
    {
        glUniform1iv(glGetUniformLocation(m_id, name.c_str()), count, values);
    }

    void Shader::SetVector2f(const std::string& name, const CU::Vector2<float>& value) const
    {
        glUniform2f(glGetUniformLocation(m_id, name.c_str()), value.x, value.y);
    }

    void Shader::SetVector3f(const std::string& name, const CU::Vector3<float>& value) const
    {
        glUniform3f(glGetUniformLocation(m_id, name.c_str()), value.x, value.y, value.z);
    }

    void Shader::SetVector4f(const std::string& name, const CU::Vector4<float>& value) const
    {
        glUniform4f(glGetUniformLocation(m_id, name.c_str()), value.x, value.y, value.z, value.w);
    }

    void Shader::SetMatrix4(const std::string& name, const glm::mat4& matrix) const
    {
        glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, false, glm::value_ptr(matrix));
    }

    int Shader::CreateShader(GLenum shaderType, const char* source)
    {
        unsigned shader = glCreateShader(shaderType);
        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);

        return shader;
    }

    void Shader::CheckCompileErrors(unsigned object, const std::string& type)
    {
        int		success;
        char	infoLog[1024];

        type != "PROGRAM" ? glGetShaderiv(object, GL_COMPILE_STATUS, &success) : glGetProgramiv(object, GL_LINK_STATUS, &success);

        if (!success)
        {
            glGetProgramInfoLog(object, 1024, nullptr, infoLog);
            std::cout << "ERROR::SHADER -> " << type << '\n' << infoLog << '\n';
        }
        //int		success;
        //char	infoLog[1024];

        //aType != "PROGRAM" ? glGetShaderiv(anObject, GL_COMPILE_STATUS, &success) : glGetProgramiv(anObject, GL_LINK_STATUS, &success);

        //if (!success)
        //    std::cout << "ERROR::SHADER -> " << aType << '\n' << infoLog << '\n';
    }
}