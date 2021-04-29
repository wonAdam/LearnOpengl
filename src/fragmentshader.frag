#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;


struct Light {
    vec3  position;
    vec3  direction;
    float innerCutOff;
    float outerCutOff;

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
    vec3 lightDir = normalize(light.position - FragPos);
    float theta     = dot(lightDir, normalize(-light.direction));
    float epsilon   = light.innerCutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);     // Mix Texture 
    
    vec3 mix_diffuse = vec3(texture(material.texture0, TexCoord) + 
                            texture(material.texture1, TexCoord) + 
                            texture(material.texture2, TexCoord)) / 3; 

    // ambient
    vec3 ambient = light.ambient * mix_diffuse;
  	
    vec3 diffuse = vec3(0.0, 0.0, 0.0);
    vec3 specular = vec3(0.0, 0.0, 0.0);
    if(theta > light.outerCutOff) 
    {       
        // diffuse 
        vec3 norm = normalize(Normal);
        float diff = max(dot(norm, lightDir), 0.0);
        diffuse = light.diffuse * diff * mix_diffuse * intensity;

        // specular
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);  
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        specular = light.specular * spec * vec3(texture(material.specular, TexCoord)) * intensity;  
    }
        


    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
} 