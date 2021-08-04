// Angabe der Version von OpenGL und dem Profil
// Hier 3.3 mit Core-Profile
#version 330 core

struct Material {
    
    sampler2D diffuseMap1;
    sampler2D specularMap1;
    
    float shininess;
    
}; 

struct Light {
    vec3 lightPos;

    vec3 ambient;
    vec3 specular;
    vec3 diffuse;
};
  

// Ausgangswert ist wieder eine Farbe, diesmal der Pixelwert
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 texCoord;


uniform vec3 objectColor;
uniform vec3 camPos;

uniform Material material;
uniform Light light;
// Hauptmethode im Shader
void main() 
{
    vec3 ambient = vec3(0.0f);
    vec3 diffuse = vec3(0.0f);
    vec3 specular = vec3(0.0f);

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.lightPos - FragPos);


	// ambient
    ambient = light.ambient * texture(material.diffuseMap1, texCoord).rgb;
    
  	
    // diffuse
    float diff = max(dot(norm, lightDir), 0.0);
    diffuse = light.diffuse * diff * texture(material.diffuseMap1, texCoord).rgb;
    

    // specular
    float specularStrength = 0.2f;
    vec3 viewDirection = normalize(camPos - FragPos);
    vec3 reflectionDirection = reflect(-lightDir, norm);
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), material.shininess);
    specular = light.specular * specAmount * texture(material.specularMap1, texCoord).rgb;

    // Check if we got invalid results in the operations
	if(any(isnan(FragColor)))
	{
		FragColor.xyz = vec3(1.f, 0.f, 1.f);
	}

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}