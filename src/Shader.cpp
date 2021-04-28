#include "Shader.h"

#include "stb_image.h"

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

void Shader::Use() const
{
    glUseProgram(ID);
}

void Shader::BindTexture() const
{
    for (auto i = 0; i < _textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, _textures[i].second);
        SetInt(_textures[i].first, i);
    }
}

void Shader::SetBool(const std::string& name, bool value) const
{
    Use();
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::SetInt(const std::string& name, int value) const
{
    Use();
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::SetFloat(const std::string& name, float value) const
{
    Use();
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::SetMat4(const std::string& name, glm::mat4 value) const
{
    Use();
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetVec3(const std::string& name, glm::vec3 value) const
{
    Use();
    float* v = glm::value_ptr<float>(value);
    glUniform3f(glGetUniformLocation(ID, name.c_str()), v[0], v[1], v[2]);
}

void Shader::SetVec3(const std::string& name, float v1, float v2, float v3) const
{
    Use();
    glUniform3f(glGetUniformLocation(ID, name.c_str()), v1, v2, v3);
}

void Shader::SetSampler2D(const std::string& name, const char* path)
{
    GLuint textureUnit = generate_Texture(path);
    _textures.push_back(std::make_pair(name, textureUnit));
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

GLuint Shader::generate_Texture(const char* path)
{
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);
    int width, height, nrChannels;
    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);

    if (data)
    {
        GLint internalFormat = nrChannels == 3 ? GL_RGB : GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, internalFormat, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);

    return texture;
}
