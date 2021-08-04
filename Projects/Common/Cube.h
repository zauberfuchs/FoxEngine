#ifndef CUBE_CLASS_H
#define CUBE_CLASS_H

#include "IMesh.h" 
#include "ISceneObject.h"

class Cube : public IMesh, public ISceneObject
{
private:
	std::vector <Vertex> m_Vertices =
	{ //			COORDINATES					/			Normals				//
		{glm::vec3(-0.5f, -0.5f, -0.5f),	 glm::vec3(0.0f,  0.0f, -1.0f),		glm::vec2(0.0f, 0.0f)},	// Non-facing side
		{glm::vec3( 0.5f, -0.5f, -0.5f),	 glm::vec3(0.0f,  0.0f, -1.0f),		glm::vec2(0.0f, 1.0f)},	// Non-facing side	
		{glm::vec3( 0.5f,  0.5f, -0.5f),	 glm::vec3(0.0f,  0.0f, -1.0f),		glm::vec2(1.0f, 1.0f)},	// Non-facing side
		{glm::vec3(-0.5f,  0.5f, -0.5f),	 glm::vec3(0.0f,  0.0f, -1.0f),		glm::vec2(1.0f, 0.0f)},	// Non-facing side

		{glm::vec3(-0.5f, -0.5f,  0.5f),	 glm::vec3(0.0f,  0.0f,  1.0f),		glm::vec2(0.0f, 0.0f)},	// facing side
		{glm::vec3( 0.5f, -0.5f,  0.5f),	 glm::vec3(0.0f,  0.0f,  1.0f),		glm::vec2(0.0f, 1.0f)},	// facing side
		{glm::vec3( 0.5f,  0.5f,  0.5f),	 glm::vec3(0.0f,  0.0f,  1.0f),		glm::vec2(1.0f, 1.0f)},	// facing side
		{glm::vec3(-0.5f,  0.5f,  0.5f),	 glm::vec3(0.0f,  0.0f,  1.0f),		glm::vec2(1.0f, 0.0f)},	// facing side

		{glm::vec3(-0.5f,  0.5f,  0.5f),	 glm::vec3(-1.0f, 0.0f,  0.0f),		glm::vec2(0.0f, 0.0f)},	// left side
		{glm::vec3(-0.5f,  0.5f, -0.5f),	 glm::vec3(-1.0f, 0.0f,  0.0f),		glm::vec2(0.0f, 1.0f)},	// left side
		{glm::vec3(-0.5f, -0.5f, -0.5f),	 glm::vec3(-1.0f, 0.0f,  0.0f),		glm::vec2(1.0f, 1.0f)},	// left side
		{glm::vec3(-0.5f, -0.5f,  0.5f),	 glm::vec3(-1.0f, 0.0f,  0.0f),		glm::vec2(1.0f, 0.0f)},	// left side

		{glm::vec3( 0.5f,  0.5f,  0.5f),	 glm::vec3(1.0f,  0.0f,  0.0f),		glm::vec2(0.0f, 0.0f)},	// right side
		{glm::vec3( 0.5f,  0.5f, -0.5f),	 glm::vec3(1.0f,  0.0f,  0.0f),		glm::vec2(0.0f, 1.0f)},	// right side
		{glm::vec3( 0.5f, -0.5f, -0.5f),	 glm::vec3(1.0f,  0.0f,  0.0f),		glm::vec2(1.0f, 1.0f)},	// right side
		{glm::vec3( 0.5f, -0.5f,  0.5f),	 glm::vec3(1.0f,  0.0f,  0.0f),		glm::vec2(1.0f, 0.0f)},	// right side

		{glm::vec3(-0.5f, -0.5f, -0.5f),	 glm::vec3(0.0f, -1.0f,  0.0f),		glm::vec2(0.0f, 0.0f)},	// bottom side
		{glm::vec3( 0.5f, -0.5f, -0.5f),	 glm::vec3(0.0f, -1.0f,  0.0f),		glm::vec2(0.0f, 1.0f)},	// bottom side
		{glm::vec3( 0.5f, -0.5f,  0.5f),	 glm::vec3(0.0f, -1.0f,  0.0f),		glm::vec2(1.0f, 1.0f)},	// bottom side
		{glm::vec3(-0.5f, -0.5f,  0.5f),	 glm::vec3(0.0f, -1.0f,  0.0f),		glm::vec2(1.0f, 0.0f)},	// bottom side

		{glm::vec3(-0.5f,  0.5f, -0.5f),	 glm::vec3(0.0f,  1.0f,  0.0f),		glm::vec3(0.0f, 0.0f, 0.0f)},	// upper side
		{glm::vec3( 0.5f,  0.5f, -0.5f),	 glm::vec3(0.0f,  1.0f,  0.0f),		glm::vec3(0.0f, 1.0f, 0.0f)},	// upper side
		{glm::vec3( 0.5f,  0.5f,  0.5f),	 glm::vec3(0.0f,  1.0f,  0.0f),		glm::vec3(1.0f, 1.0f, 0.0f)},	// upper side
		{glm::vec3(-0.5f,  0.5f,  0.5f),	 glm::vec3(0.0f,  1.0f,  0.0f),		glm::vec3(1.0f, 0.0f, 0.0f)}	// upper side
	};


	std::vector <GLuint> m_Indices = {  // note that we start from 0!
		 0,  3,  2,				// 1.	triangle	Non-facing side
		 2,  1,  0,				// 2.	triangle	Non-facing side
		 4,  5,  6,				// 3.	triangle	facing side
		 6,  7,  4,				// 4.	triangle	facing side
		 8,  9, 10,				// 5.	triangle	left side
		10, 11,  8,				// 6.	triangle	left side
		12, 15, 14,				// 7.	triangle	right side
		14, 13, 12,				// 8.	triangle	right side
		18, 19, 16,				// 9.	triangle	bottom side
		16, 17, 18,				// 10.	triangle	bottom side
		22, 21, 20,				// 11.	triangle	upper side
		20, 23, 22				// 12.	triangle	upper side
	};

public:
	// Initializes the mesh
	Cube();

	// setups the mesh
	void setupMesh();

	// Draws the mesh
	void Draw(Shader& shader, Camera& camera);

	// adds a texture to the mesh
	void addTexture(const std::string& filepath, const std::string& type);
	void translate(glm::mat4& around, glm::vec3& eulerAngles);
	void rotate(glm::mat4& around, glm::vec3& eulerAngles);
	void scale(glm::mat4& around, glm::vec3& eulerAngles);

	glm::mat4& getModelMatrix();

	void setColor(glm::vec3& color);
	void addLightSource(std::shared_ptr<Light> lightSource);
	void setReflections(const int& hasAmbient, const int& hasDiffuse, const int& hasSpecular);
	void setMaterial(Material& material);
};
#endif