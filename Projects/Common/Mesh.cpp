#include "Mesh.h"
#include <stddef.h> 
Mesh::Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices)
{
	Mesh::m_Vertices = vertices;
	Mesh::m_Indices = indices;
	Mesh::m_Textures = m_Textures;
	Mesh::m_Model = glm::mat4(1.0f);
	Mesh::objectColor = glm::vec3(0.0f);
	Mesh::setupMesh();
}

Mesh::Mesh(std::vector <Vertex> vertices, std::vector <GLuint> indices, std::vector <Texture> textures)
{
	this->m_Vertices = vertices;
	this->m_Indices = indices;
	this->m_Textures = textures;
	this->VAO = VertexArray();
	Mesh::m_Model = glm::mat4(1.0f);
	Mesh::objectColor = glm::vec3(0.0f);
	Mesh::setupMesh();
}


void Mesh::setupMesh()
{
	
	VAO.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VertexBuffer VBO(m_Vertices);
	// Generates Element Buffer Object and links it to indices
	IndexBuffer IBO(m_Indices);


	VertexBufferLayout layout;
	// Generates VertexBufferLayout
	// Links VBO attributes such as coordinates and colors to VAO
	layout.Push<float>(3);
	layout.Push<float>(3);
	layout.Push<float>(2);
	VAO.AddBuffer(VBO, layout);
	// Unbind all to prevent accidentally modifying them
	VAO.Unbind();
	VBO.Unbind();
	IBO.Unbind();
}



void Mesh::addTexture(const std::string& filepath, const std::string& type)
{
	m_Textures.emplace_back(filepath, type);
}

void Mesh::translate(glm::mat4& around, glm::vec3& eulerAngles)
{
	m_Model = glm::translate(around, eulerAngles);
}

void Mesh::rotate(glm::mat4& around, glm::vec3& eulerAngles)
{
	if (eulerAngles.x != 0)
	{
		m_Model = glm::rotate(around, glm::radians(eulerAngles.x), glm::vec3(1.0f, 0.0f, 0.0f));
	}
	if (eulerAngles.y != 0)
	{
		m_Model = glm::rotate(around, glm::radians(eulerAngles.y), glm::vec3(0.0f, 1.0f, 0.0f));
	}
	if (eulerAngles.z != 0)
	{
		m_Model = glm::rotate(around, glm::radians(eulerAngles.z), glm::vec3(0.0f, 0.0f, 1.0f));
	}
}

void Mesh::scale(glm::mat4& around, glm::vec3& eulerAngles)
{
	m_Model = glm::scale(around, eulerAngles);
}

void Mesh::setColor(glm::vec3& Color)
{
	Mesh::objectColor = Color;
}

void Mesh::addLightSource(std::shared_ptr<Light> lightSource)
{
	Mesh::lightSources.push_back(lightSource);
}

void Mesh::setReflections(const int& hasAmbient, const int& hasDiffuse, const int& hasSpecular)
{
	Mesh::hasAmbient = hasAmbient;
	Mesh::hasDiffuse = hasDiffuse;
	Mesh::hasSpecular = hasSpecular;
}

void Mesh::setMaterial(Material& material)
{
	Mesh::material = material;
}

glm::mat4& Mesh::getModelMatrix()
{
	return m_Model;
}

void Mesh::Draw(Shader& shader, Camera& camera)
{
	// Bind shader to be able to access uniforms
	shader.Bind();
	VAO.Bind();

	camera.updateMatrix(shader);

	// Keep track of how many of each type of textures we have
	unsigned int numDiffuse = 1;
	unsigned int numSpecular = 1;
	unsigned int numNormal = 1;
	unsigned int numHeight = 1;
	unsigned int numTextures = 0;
	for (Texture& t : m_Textures) 
	{
		glActiveTexture(GL_TEXTURE0 + numTextures);
		std::string num;
		std::string type = t.m_type;
		if (type == "diffuseMap")
			num = to_string(numDiffuse++);
		else if (type == "specularMap")
			num = to_string(numSpecular++);
		else if (type == "normalMap")
			num = to_string(numNormal++);
		else if (type == "heightMap")
			num = to_string(numHeight++);
		else
			num = "";

		shader.SetUniform1i((type + num).c_str(), numTextures);
		glBindTexture(GL_TEXTURE_2D, t.m_ID);
		numTextures++;
	}

	shader.SetUniformMat4f("model", m_Model);

	shader.SetUniform3f("objectColor", objectColor);
	shader.SetUniform3f("camPos", camera.Position);
	shader.SetUniform1f("numPointlights", lightSources.size());
	for (int i = 0; i < lightSources.size(); i++) {
		if(lightSources[i]->type == POINT_LIGHT)
		{
			shader.SetUniform3f("pointLights[" + to_string(i) + "].position", lightSources[i]->position);
			shader.SetUniform1f("pointLights[" + to_string(i) + "].constant", lightSources[i]->constant);
			shader.SetUniform1f("pointLights[" + to_string(i) + "].linear", lightSources[i]->linear);
			shader.SetUniform1f("pointLights[" + to_string(i) + "].quadratic", lightSources[i]->quadratic);
			shader.SetUniform3f("pointLights[" + to_string(i) + "].ambient", material.ambient);
			shader.SetUniform3f("pointLights[" + to_string(i) + "].diffuse", material.diffuse);
			shader.SetUniform3f("pointLights[" + to_string(i) + "].specular", material.specular);
			shader.SetUniform1f("material.shininess", material.shininess);
		}
		else if(lightSources[i]->type == DIRECTIONAL_LIGHT)
		{
			shader.SetUniform3f("dirLight.direction", lightSources[i]->direction);
			shader.SetUniform3f("dirLight.ambient", material.ambient);
			shader.SetUniform3f("dirLight.diffuse", material.diffuse);
			shader.SetUniform3f("dirLight.specular", material.specular);
			shader.SetUniform1f("material.shininess", material.shininess);
		}

	}


	// Draw the actual mesh
	glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, nullptr);
	shader.Unbind();
	VAO.Unbind();
	glActiveTexture(GL_TEXTURE0);
}