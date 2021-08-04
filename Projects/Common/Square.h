#ifndef SQUARE_CLASS_H
#define SQUARE_CLASS_H

#include "IMesh.h" 
#include "ISceneObject.h"

class Square: public IMesh, public ISceneObject
{
private:
	std::vector <Vertex> m_Vertices =
	{ //			COORDINATES				/			Normals					//
		{glm::vec3(-0.5f,  0.0f, -0.5f),	 glm::vec3(0.0f,  1.0f,  0.0f),		glm::vec2(0.0f, 0.0f)},	// upper side
		{glm::vec3( 0.5f,  0.0f, -0.5f),	 glm::vec3(0.0f,  1.0f,  0.0f),		glm::vec2(0.0f, 1.0f)},	// upper side
		{glm::vec3( 0.5f,  0.0f,  0.5f),	 glm::vec3(0.0f,  1.0f,  0.0f),		glm::vec2(1.0f, 1.0f)},	// upper side
		{glm::vec3(-0.5f,  0.0f,  0.5f),	 glm::vec3(0.0f,  1.0f,  0.0f),		glm::vec2(1.0f, 0.0f)}	// upper side
	};


	std::vector <GLuint> m_Indices = {  // note that we start from 0!
		0, 3, 2,				// 1.	triangle	bottom side
		2, 1, 0,				// 2.	triangle	bottom side
	};
	//Texture texture;
public:
	// Initializes the mesh
	Square();

	// setups the mesh
	void setupMesh();

	// Draws the mesh
	void Draw(Shader& shader, Camera& camera);

	// adds a texture to the mesh
	void addTexture(const std::string& filepath, const std::string& type);
	void translate(glm::mat4& around, glm::vec3& eulerAngles);
	void rotate(glm::mat4& around, glm::vec3& eulerAngles);
	void scale(glm::mat4& around, glm::vec3& eulerAngles);
	
	glm::mat4& Square::getModelMatrix();

	void setColor(glm::vec3& color);
	void addLightSource(std::shared_ptr<Light> lightSource);
	void setReflections(const int& hasAmbient, const int& hasDiffuse, const int& hasSpecular);
	void setMaterial(Material& material);
};
#endif