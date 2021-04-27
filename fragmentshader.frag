#version 330 core
out vec4 FragColor;

in vec3 vertexColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;

uniform vec3 lightColor;
uniform vec3 lightPos;

void main()
{
    vec4 objectColor = vec4(0.0, 0.0, 0.0, 1.0);
    objectColor += texture(texture1, TexCoord) / 3;
    objectColor += texture(texture2, TexCoord) / 3;
    objectColor += texture(texture3, TexCoord) / 3;

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * objectColor.rgb;
    FragColor = vec4(result, 1.0);
} 