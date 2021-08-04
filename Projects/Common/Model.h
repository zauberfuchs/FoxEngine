#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>

#include "Mesh.h"
#include "Texture.h"
#include "Camera.h"
#include "ISceneObject.h"

class Model: public ISceneObject
{
public:
	// stores all the textures loaded so far, 
	// optimization to make sure textures aren't loaded more than once.
	std::vector<Texture> textures_loaded;

	Model(const char* path);

	void Draw(Shader& shader, Camera& camera);

	void translate(glm::mat4& around, glm::vec3& eulerAngles);
	void rotate(glm::mat4& around, glm::vec3& eulerAngles);
	void scale(glm::mat4& around, glm::vec3& eulerAngles);

	glm::mat4& getModelMatrix();

	void setColor(glm::vec3& Color);
	void addLightSource(std::shared_ptr<Light> lightSource);
	void setReflections(const int& hasAmbient, const int& hasDiffuse, const int& hasSpecular);
	void setMaterial(Material& material);

private:
	// model data
	std::vector<Mesh> m_Meshes;
	std::string m_Directory;

	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
		std::string typeName);
	Texture TextureFromFile(const std::string& path, const std::string& type);
	Material loadMaterial(aiMaterial* mat);
};
#endif