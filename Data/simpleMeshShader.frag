// Angabe der Version von OpenGL und dem Profil
// Hier 3.3 mit Core-Profile
#version 330 core

struct Material {
    vec3 ambient;
    vec3 specular;
    float shininess;
    vec3 diffuse;
}; 
  

// Ausgangswert ist wieder eine Farbe, diesmal der Pixelwert
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 texCoord;

uniform vec3 lightPos; 
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 camPos;

uniform int hasTexture;

uniform Material material;

uniform sampler2D u_Texture;

// Hauptmethode im Shader
void main() 
{
    vec3 ambient = vec3(0.0f);
    vec3 diffuse = vec3(0.0f);
    vec3 specular = vec3(0.0f);
    vec4 tex = vec4(1.0f);

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);


	// ambient
    ambient = lightColor * material.ambient;
    
  	
    // diffuse
    float diff = max(dot(norm, lightDir), 0.0);
    diffuse = lightColor * (diff * material.diffuse);
    

    // specular
    float specularStrength = 0.2f;
    vec3 viewDirection = normalize(camPos - FragPos);
    vec3 reflectionDirection = reflect(-lightDir, norm);
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), material.shininess);
    specular = lightColor * (specAmount * material.specular);
    

    // texture
    if(hasTexture == 1)
    {
        tex = texture(u_Texture, texCoord);
    }

    // Check if we got invalid results in the operations
	if(any(isnan(FragColor)))
	{
		FragColor.xyz = vec3(1.f, 0.f, 1.f);
	}

    vec3 result = (ambient + diffuse + specular) * objectColor;

    FragColor = tex * vec4(result, 1.0);
}