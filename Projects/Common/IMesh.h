#ifndef IMESH_INTERFACE_H
#define IMESH_INTERFACE_H

#include <string>

#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Camera.h"
#include "Texture.h"

using namespace std;

struct Material
{
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
};
enum LightSourceType
{
	POINT_LIGHT, DIRECTIONAL_LIGHT, SPOT_LIGHT
};
struct Light 
{
	LightSourceType type;

	glm::vec3 direction;
	glm::vec3 position;

	float constant;
	float linear;
	float quadratic;

	float cutOff;
	float outerCutOff;
};

class IMesh
{
public:
	std::vector <Vertex> m_Vertices;
	std::vector <GLuint> m_Indices;
	std::vector <Texture> m_Textures;

	VertexArray VAO;

	glm::vec3 objectColor;

	Material material;

	GLuint hasTexture = 0;

	// setups the mesh
	virtual void setupMesh() = 0;
	// Draws the mesh
	virtual void Draw(Shader& shader, Camera& camera) = 0;
	// adds a texture to the mesh
	virtual void addTexture(const std::string& filepath, const std::string& type) = 0;

	virtual void setColor(glm::vec3& Color) = 0;
	virtual void addLightSource(std::shared_ptr<Light> lightSource) = 0;
	virtual void setMaterial(Material& material) = 0;
};

#endif