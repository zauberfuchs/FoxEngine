#include "Cube.h"

Cube::Cube()
{
	Cube::m_Vertices = m_Vertices;
	Cube::m_Indices = m_Indices;
	Cube::m_Textures = m_Textures;
	Cube::m_Vertices = m_Vertices;
	Cube::m_Indices = m_Indices;
	Cube::m_Textures = m_Textures;
	Cube::m_Model = glm::mat4(1.0f);
	Cube::objectColor = glm::vec3(0.0f);
	Cube::setupMesh();
}

void Cube::setupMesh()
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

void Cube::addTexture(const std::string& filepath, const std::string& type)
{
	m_Textures.emplace_back(filepath, type);
}

void Cube::translate(glm::mat4& around, glm::vec3& eulerAngles)
{
	m_Model = glm::translate(around, eulerAngles);
}

void Cube::rotate(glm::mat4& around, glm::vec3& eulerAngles)
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


void Cube::scale(glm::mat4& around, glm::vec3& eulerAngles)
{
	m_Model = glm::scale(around, eulerAngles);
}

glm::mat4& Cube::getModelMatrix()
{
	return m_Model;
}

void Cube::setColor(glm::vec3& Color)
{
	Cube::objectColor = Color;
}

void Cube::addLightSource(std::shared_ptr<Light> lightSource)
{
	Cube::lightSources.push_back(lightSource);
}

void Cube::setReflections(const int& hasAmbient, const int& hasDiffuse, const int& hasSpecular)
{
	Cube::hasAmbient = hasAmbient;
	Cube::hasDiffuse = hasDiffuse;
	Cube::hasSpecular = hasSpecular;
}

void Cube::setMaterial(Material& material)
{
	Cube::material = material;
}

void Cube::Draw(Shader& shader, Camera& camera)
{
	// Bind shader to be able to access uniforms
	shader.Bind();
	VAO.Bind();
	camera.updateMatrix(shader);

	// Keep track of how many of each type of textures we have
	unsigned int numDiffuse = 0;
	unsigned int numSpecular = 0;
	for (unsigned int i = 0; i < m_Textures.size(); i++)
	{
		std::string num;
		std::string type = m_Textures[i].m_type;
		if (type == "diffuseMap")
		{
			num = std::to_string(numDiffuse++);
			hasDiffuseMap = 1;
		}
		else if (type == "specularMap")
		{
			num = std::to_string(numSpecular++);
			hasSpecularMap = 1;
		}
		else
		{
			num = "";
		}

		shader.SetUniform1i((type + num).c_str(), i);
		m_Textures[i].Bind();
	}
	for (int i = 0; i < lightSources.size(); i++) {
		if (lightSources[i]->type == POINT_LIGHT)
		{
			shader.SetUniform3f("lightPos", lightSources[0]->position);
			shader.SetUniform3f("lightColor", lightSources[0]->color);
		}
		else if (lightSources[i]->type == DIRECTIONAL_LIGHT)
		{
			shader.SetUniform3f("lightPos", lightSources[0]->position);
			shader.SetUniform3f("lightColor", lightSources[0]->color);
		}
	}
	shader.SetUniform1i("hasAmbient", hasAmbient);
	shader.SetUniform1i("hasDiffuse", hasDiffuse);
	shader.SetUniform1i("hasSpecular", hasSpecular);
	shader.SetUniform1i("hasTexture", hasTexture);

	shader.SetUniform1i("hasDiffuseMap", hasDiffuseMap);
	shader.SetUniform1i("hasSpecularMap", hasSpecularMap);

	shader.SetUniformMat4f("model", m_Model);

	shader.SetUniform3f("objectColor", objectColor);
	shader.SetUniform3f("camPos", camera.Position);

	shader.SetUniform3f("material.ambient", material.ambient);
	shader.SetUniform3f("material.diffuse", material.diffuse);
	shader.SetUniform3f("material.specular", material.specular);
	shader.SetUniform1f("material.shininess", material.shininess);

	// Draw the actual mesh
	glDrawElements(GL_TRIANGLES, (GLsizei)m_Indices.size(), GL_UNSIGNED_INT, nullptr);
	shader.Unbind();
	VAO.Unbind();
}
