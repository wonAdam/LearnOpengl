#version 330 core
out vec4 FragColor;

in vec3 vertexColor;
in vec2 TexCoord;
  
uniform vec3 diffuse;

void main()
{
    FragColor = vec4(diffuse, 1.0);
}