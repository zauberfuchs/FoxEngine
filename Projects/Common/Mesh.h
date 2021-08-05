#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include "IMesh.h"
#include "ISceneObject.h"

class Mesh: public IMesh, public ISceneObject
{
public:
	// Initializes the mesh
	Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices);
	Mesh(std::vector <Vertex> vertices, std::vector <GLuint> indices, std::vector <Texture> textures);
	// setups the mesh
	void setupMesh();

	// Draws the mesh
	void Draw(Shader& shader, Camera& camera);

	// adds a texture to the mesh
	void addTexture(const std::string& filepath, const std::string& type);
	void translate(glm::mat4& around, glm::vec3& eulerAngles);
	void rotate(glm::mat4& around, glm::vec3& eulerAngles);
	void scale(glm::mat4& around, glm::vec3& eulerAngles);

	glm::mat4& Mesh::getModelMatrix();

	void setColor(glm::vec3& color);
	void addLightSource(std::shared_ptr<Light> lightSource);
	void setMaterial(Material& material);
};
#endif