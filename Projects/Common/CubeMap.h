#ifndef CUBEMAP_CLASS_H
#define CUBEMAP_CLASS_H

#include "IMesh.h" 
#include "ISceneObject.h"

class CubeMap
{
public:
	CubeMap();
	void Draw(Shader& shader, Camera& camera);


private:
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_Components;

	GLuint m_ID;
	GLuint skyboxVAO, skyboxVBO, skyboxEBO;

	std::vector<std::string> m_Faces
	{
			"../Data/Textures/Skybox/right.png",
			"../Data/Textures/Skybox/left.png",
			"../Data/Textures/Skybox/top.png",
			"../Data/Textures/Skybox/bottom.png",
			"../Data/Textures/Skybox/front.png",
			"../Data/Textures/Skybox/back.png"
	};
	
	void load();
	void setupCubeMap();
};

#endif