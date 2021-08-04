// Angabe der Version von OpenGL und dem Profil
// Hier 3.3 mit Core-Profile
#version 330 core
// Layout der Vertex-Daten, zuvor spezifiziert 
// über die VertexAttribPointer
// Positions/Coordinates
layout (location = 0) in vec3 vPos;
// Normals
layout (location = 1) in vec3 vNormal;
// Texture Coordinates
layout (location = 2) in vec2 vTex;

out vec3 FragPos;
out vec3 Normal;
out vec2 texCoord;
// Uniform-Variable zum Setzen der aktuellen Transformationsmatrix

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// Hauptmethode im Shader
void main() 
{
	FragPos = vec3(model * vec4(vPos, 1.0));

	Normal = mat3(transpose(inverse(model))) * vNormal; 

	// Assigns the texture coordinates from the Vertex Data to "texCoord"
	texCoord = vTex;

	gl_Position = projection * view * vec4(FragPos, 1.0);
}