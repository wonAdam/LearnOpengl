#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;


struct Light {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;

uniform vec3 viewPos;

struct Material {
    // diffuse;
    sampler2D texture0;
    sampler2D texture1;
    sampler2D texture2;

    sampler2D specular;
    float shininess;
}; 
  

uniform Material material;

void main()
{
    vec3 mix_diffuse = vec3(texture(material.texture0, TexCoord) + 
                            texture(material.texture1, TexCoord) + 
                            texture(material.texture2, TexCoord)) / 3; 

    // ambient
    vec3 ambient = light.ambient * mix_diffuse;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * mix_diffuse;
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));  
        
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);

} 