#version 330 core
out vec4 FragColor;

in vec3 vertexColor;
in vec2 TexCoord;
  
uniform vec3 lightColor;

void main()
{
    FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}