#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>

// Structure to standardize the vertices used in the meshes
struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texUV;
};

class VertexBuffer
{
private:
	GLuint m_ID;

public:
	VertexBuffer(std::vector<Vertex>& vertices);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

};
#endif