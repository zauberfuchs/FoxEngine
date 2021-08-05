#include "Square.h"

Square::Square()
{
	Square::m_Vertices = m_Vertices;
	Square::m_Indices = m_Indices;
	Square::m_Textures = m_Textures;
	Square::m_Model = glm::mat4(1.0f);
	Square::objectColor = glm::vec3(0.0f);
	Square::setupMesh();
}

void Square::setupMesh()
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

void Square::addTexture(const std::string& filepath, const std::string& type)
{
	m_Textures.emplace_back(filepath, type);
	hasTexture = 1;
}

void Square::translate(glm::mat4& around, glm::vec3& eulerAngles)
{
	m_Model = glm::translate(around, eulerAngles);
}

void Square::rotate(glm::mat4& around, glm::vec3& eulerAngles)
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

void Square::scale(glm::mat4& around, glm::vec3& eulerAngles)
{
	m_Model = glm::scale(around, eulerAngles);
}

void Square::setColor(glm::vec3& Color)
{
	Square::objectColor = Color;
}

void Square::addLightSource(std::shared_ptr<Light> lightSource)
{
	Square::lightSources.push_back(lightSource);
}

void Square::setMaterial(Material& material)
{
	Square::material = material;
}

glm::mat4& Square::getModelMatrix()
{
	return m_Model;
}

void Square::Draw(Shader& shader, Camera& camera)
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
		}
		else if (type == "specularMap")
		{
			num = std::to_string(numSpecular++);
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
			shader.SetUniform3f("pointLights[" + to_string(i) + "].position", lightSources[i]->position);
			shader.SetUniform1f("pointLights[" + to_string(i) + "].constant", lightSources[i]->constant);
			shader.SetUniform1f("pointLights[" + to_string(i) + "].linear", lightSources[i]->linear);
			shader.SetUniform1f("pointLights[" + to_string(i) + "].quadratic", lightSources[i]->quadratic);
			shader.SetUniform3f("pointLights[" + to_string(i) + "].ambient", material.ambient);
			shader.SetUniform3f("pointLights[" + to_string(i) + "].diffuse", material.diffuse);
			shader.SetUniform3f("pointLights[" + to_string(i) + "].specular", material.specular);
			shader.SetUniform1f("material.shininess", material.shininess);
		}
		else if (lightSources[i]->type == DIRECTIONAL_LIGHT)
		{
			shader.SetUniform3f("dirLight.direction", lightSources[i]->direction);
			shader.SetUniform3f("dirLight.ambient", material.ambient);
			shader.SetUniform3f("dirLight.diffuse", material.diffuse);
			shader.SetUniform3f("dirLight.specular", material.specular);
			shader.SetUniform1f("material.shininess", material.shininess);
		}

	}
	shader.SetUniform1i("hasTexture", hasTexture);

	shader.SetUniformMat4f("model", m_Model);

	shader.SetUniform3f("objectColor", objectColor);
	shader.SetUniform3f("camPos", camera.Position);

	// Draw the actual mesh
	glDrawElements(GL_TRIANGLES, (GLsizei)m_Indices.size(), GL_UNSIGNED_INT, nullptr);
	if(m_Textures.size()>0)
		m_Textures[0].Unbind();

	shader.Unbind();
	VAO.Unbind();
}
