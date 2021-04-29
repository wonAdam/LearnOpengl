#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

struct DirLight {
    vec3 direction;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  
uniform bool hasDirLight;
uniform DirLight dirLight;

struct PointLight {    
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;  

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  
#define MAX_POINTLIGHT 10  
uniform int n_of_point_lights = 0;
uniform PointLight pointLights[MAX_POINTLIGHT];

struct SpotLight {    
    vec3 position;
    vec3 direction;
    float cutOff;    
    float outerCutOff;

    float constant;
    float linear;
    float quadratic; 

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  
#define MAX_SPOTLIGHT 10  
uniform int n_of_spot_lights = 0;
uniform SpotLight spotLights[MAX_SPOTLIGHT];

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


vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 diffuse_tex);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir,  vec3 diffuse_tex);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 diffuse_tex);

void main()
{
    vec3 mix_diffuse = vec3(texture(material.texture0, TexCoord) + 
                            texture(material.texture1, TexCoord) + 
                            texture(material.texture2, TexCoord)) / 3; 

      vec3 viewDir = normalize(viewPos - FragPos);

  	  // define an output color value
      vec3 result = vec3(0.0);

      // add the directional light's contribution to the output
      if(hasDirLight)
          result += CalcDirLight(dirLight, Normal, viewDir, mix_diffuse);

      // do the same for all point lights
      for(int i = 0; i < n_of_point_lights; i++)
  	    result += CalcPointLight(pointLights[i], Normal, FragPos, viewDir, mix_diffuse);

      // and add others lights as well (like spotlights)
      for(int i = 0; i < n_of_spot_lights; i++)
          result += CalcSpotLight(spotLights[i], Normal, FragPos, viewDir, mix_diffuse);

    FragColor = vec4(result, 1.0);
} 



vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 diffuse_tex)
{
    vec3 lightDir = normalize(-light.direction);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // combine results
    vec3 ambient  = light.ambient  * diffuse_tex;
    vec3 diffuse  = light.diffuse  * diff * diffuse_tex;
    vec3 specular = light.specular * spec * diffuse_tex;
    return (ambient + diffuse + specular);
}  


vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir,  vec3 diffuse_tex)
{
    vec3 lightDir = normalize(light.position - fragPos);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance));    

    // combine results
    vec3 ambient  = light.ambient  * diffuse_tex;
    vec3 diffuse  = light.diffuse  * diff * diffuse_tex;
    vec3 specular = light.specular * spec * diffuse_tex;
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
} 

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 diffuse_tex)
{
    vec3 lightDir = normalize(light.position - fragPos);    
    
    float theta     = dot(lightDir, normalize(-light.direction));
    float epsilon   = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);  

    float diff = 0.0;
    float spec = 0.0;
    if(theta > light.cutOff)
    {
        // diffuse shading
        diff = max(dot(normal, lightDir), 0.0);

        // specular shading
        vec3 reflectDir = reflect(-lightDir, normal);
        spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    }

    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance));   

    // combine results
    vec3 ambient  = light.ambient  * diffuse_tex;
    vec3 diffuse  = light.diffuse  * diff * diffuse_tex;
    vec3 specular = light.specular * spec * diffuse_tex;
//    ambient *= attenuation;
//    diffuse *= attenuation;
//    specular *= attenuation;
    ambient *= intensity;
    diffuse *= intensity;
    specular *= intensity;
    return (ambient + diffuse + specular);
}

