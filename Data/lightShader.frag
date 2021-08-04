// Angabe der Version von OpenGL und dem Profil
// Hier 3.3 mit Core-Profile
#version 330 core

// Ausgangswert ist wieder eine Farbe, diesmal der Pixelwert
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 texCoord;


uniform vec3 lightPos; 
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 camPos;


// Hauptmethode im Shader
void main() 
{
    vec3 result = vec3(1.0f);
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);


	// ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
    result += ambient;
    
    
  	
    // diffuse
    float diffuseStrength = 0.5f;
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * diffuseStrength * lightColor;
    result += diffuse;
    
    

    // specular
    float specularStrength = 0.2f;
    vec3 viewDirection = normalize(camPos - FragPos);
    vec3 reflectionDirection = reflect(-lightDir, norm);
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 256);
    vec3 specular = specAmount * specularStrength * lightColor;
    result += specular;

    // Check if we got invalid results in the operations
	if(any(isnan(FragColor)))
	{
		FragColor.xyz = vec3(1.f, 0.f, 1.f);
	}

    result *= objectColor;

    FragColor = vec4(result, 1.0);
}