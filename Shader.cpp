#include "Shader.h"

Shader::Shader(const char* vertexFilePath, const char* fragmentFilePath)
{
    std::string vertexCode = read_shader(vertexFilePath);
    std::string fragmentCode = read_shader(fragmentFilePath);

    GLint vShader = glCreateShader(GL_VERTEX_SHADER);
    GLint fShader = glCreateShader(GL_FRAGMENT_SHADER);

    const GLchar* vCode = vertexCode.c_str();
    const GLchar* fCode = fragmentCode.c_str();

    glShaderSource(vShader, 1, &vCode, NULL);
    glShaderSource(fShader, 1, &fCode, NULL);

    glCompileShader(vShader);
    check_shader_compile_error(vShader);
    glCompileShader(fShader);
    check_shader_compile_error(fShader);

    ID = glCreateProgram();
    glAttachShader(ID, vShader);
    glAttachShader(ID, fShader);
    glLinkProgram(ID);
    check_program_link_error(ID);


    glDeleteShader(vShader);
    glDeleteShader(fShader);
}

void Shader::use()
{
    glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
 
std::string Shader::read_shader(const char* path) const
{
    std::ifstream file(path);
    std::stringstream shader;

    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try 
    {
        shader << file.rdbuf();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << e.code() << std::endl;
    }

    return shader.str();
}

void Shader::check_shader_compile_error(GLint shader) const
{
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

void Shader::check_program_link_error(GLint program) const
{
    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
}
