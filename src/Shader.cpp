#include "Shader.h"

#include <GLEW/glew.h>

#include <iostream>
#include <fstream>
#include <sstream>


Shader::Shader(const std::string& filepath)
    : m_filepath(filepath)
{
    ShaderProgramSource source = ParseShader(filepath);

    m_rendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
    glDeleteProgram(m_rendererID);
}

void Shader::Bind() const
{
    glUseProgram(m_rendererID);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

void Shader::SetUniform1i(const std::string& name, int value)                              { glUniform1i(GetUniformLocation(name), value);          }
void Shader::SetUniform1f(const std::string& name, float value)                            { glUniform1f(GetUniformLocation(name), value);          }
void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) { glUniform4f(GetUniformLocation(name), v0, v1, v2, v3); }

int Shader::GetUniformLocation(const std::string& name)
{
    if (m_uniforms.contains(name)) {
        return (m_uniforms[name]);
    }

    int location = glGetUniformLocation(m_rendererID, name.c_str());
    if (location == -1) {
        std::cout << "Warning: uniform '" << name << "'" << std::endl;
    }
    m_uniforms[name] = location;
    return location;
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath) {
    std::ifstream stream(filepath);

    enum class ShaderType {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else if (type != ShaderType::NONE) {
            ss[(int)type] << line << '\n';
        }
    }
    return { ss[0].str(), ss[1].str() };
}

uint32_t Shader::CompileShader(uint32_t type, const std::string& source) {
    uint32_t id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

uint32_t Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
    uint32_t program = glCreateProgram();
    uint32_t vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    uint32_t fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}
