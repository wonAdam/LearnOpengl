#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

out vec3 vertexColor;
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
    gl_Position = proj * view * model * vec4(aPos, 1.0f);
    TexCoord = aTexCoord;

    // Normal = mat3(transpose(inverse(model))) * aNormal;
    // Normal = vec3(model * vec4(aNormal, 0.0f));
    Normal = mat3(model) * aNormal;
    FragPos = vec3(model * vec4(aPos, 1.0));
}