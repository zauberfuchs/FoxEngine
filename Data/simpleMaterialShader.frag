// Angabe der Version von OpenGL und dem Profil
// Hier 3.3 mit Core-Profile
#version 330 core

struct Material {
    sampler2D diffuseMap1;
    sampler2D specularMap1;
    float shininess;
}; 

struct DirLight {
    vec3 direction;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

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
#define NR_POINT_LIGHTS 1  
// Ausgangswert ist wieder eine Farbe, diesmal der Pixelwert
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 texCoord;


uniform vec3 objectColor;
uniform vec3 camPos;

uniform sampler2D u_Texture;

uniform Material material;

uniform int hasTexture;


uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLight;

// function prototypes
vec3 CalcDirectionalLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);



// Hauptmethode im Shader
void main() 
{  
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(camPos - FragPos);
    vec3 result;

    vec4 tex = vec4(1.0f);

    // phase 1: directional lighting
    result = CalcDirectionalLight(dirLight, norm, viewDir);
    // phase 2: point lights
    for(int i = 0; i < NR_POINT_LIGHTS; i++) 
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
    // phase 3: spot light
    //result += CalcSpotLight(spotLight, norm, FragPos, viewDir);

    // Check if we got invalid results in the operations
	if(any(isnan(FragColor)))
	{
		FragColor.xyz = vec3(1.f, 0.f, 1.f);
	}

    // texture
    if(hasTexture == 1)
    {
        tex = texture(u_Texture, texCoord);
    }

    FragColor = tex * vec4(result, 1.0);
    //FragColor = vec4(result, 1.0);
}

vec3 CalcDirectionalLight(DirLight light, vec3 normal, vec3 viewDirection)
{
    vec3 lightDir = normalize(-light.direction);
    vec3 halfwayDir = normalize(lightDir + viewDirection);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    float specAmount = pow(max(dot(normal, halfwayDir), 0.0f), material.shininess);
    // combine results
    vec3 ambient  = light.ambient;
    vec3 diffuse  = light.diffuse  * diff;
    vec3 specular = light.specular * specAmount;
    vec3 result;
    if(objectColor != 0)
    {
       result = (ambient + diffuse + specular) * objectColor;
    }
    else
    {
        result = (ambient + diffuse + specular);
    }
    return result;
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDirection)
{
    vec3 lightDir = normalize(light.position - fragPos);
    vec3 halfwayDir = normalize(lightDir + viewDirection);
    float specAmount = 0;
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    if(diff > 0)
        specAmount = pow(max(dot(normal, halfwayDir), 0.0f), material.shininess);
    
    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
  			            light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient  = light.ambient;
    vec3 diffuse  = light.diffuse  * diff;
    vec3 specular = light.specular * specAmount;
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    vec3 result;
    if(objectColor != 0)
    {
       result = (ambient + diffuse + specular) * objectColor;
    }
    else
    {
        result = (ambient + diffuse + specular);
    }
    return result;
} 

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDirection)
{
     vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectionDirection = reflect(-lightDir, normal);
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), material.shininess);
    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
  			            light.quadratic * (distance * distance));     
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = light.ambient;
    vec3 diffuse = light.diffuse * diff;
    vec3 specular = light.specular * specAmount;
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}