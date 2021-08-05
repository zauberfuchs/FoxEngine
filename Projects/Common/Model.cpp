#include "Model.h"


Model::Model(const char* path)
{
	loadModel(path);
}

void Model::Draw(Shader& shader, Camera& camera)
{
	for (Mesh& m : m_Meshes)
		m.Draw(shader, camera);
}

void Model::translate(glm::mat4& around, glm::vec3& eulerAngles)
{
	for (Mesh& m : m_Meshes)
		m.translate(around, eulerAngles);
}

void Model::rotate(glm::mat4& around, glm::vec3& eulerAngles)
{
	for (Mesh& m : m_Meshes)
		m.rotate(around, eulerAngles);
}

void Model::scale(glm::mat4& around, glm::vec3& eulerAngles)
{
	for (Mesh& m : m_Meshes)
		m.scale(around, eulerAngles);
}

glm::mat4& Model::getModelMatrix()
{
	//gibt mir die letzte model matrize die bis zum schluss unverändert ist
	//besser wäre es wenn das model eine einzige matrize hat und diese nutzt?!
	return m_Meshes.back().m_Model;
}

void Model::setColor(glm::vec3& color)
{
	for (Mesh& m : m_Meshes)
		m.setColor(color);
}

void Model::addLightSource(std::shared_ptr<Light> lightSource)
{
	for (Mesh& m : m_Meshes)
		m.addLightSource(lightSource);
}

void Model::setMaterial(Material& material)
{
	for (Mesh& m : m_Meshes)
		m.setMaterial(material);
}

void Model::loadModel(std::string path)
{
	// read file via ASSIMP
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	// check for errors
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}
	// retrieve the directory path of the filepath
	m_Directory = path.substr(0, path.find_last_of('/'));
	// process ASSIMP's root node recursively
	processNode(scene->mRootNode, scene);
}
// processes a node in a recursive fashion
// processes each individual mesh located at the node and 
// repeats this process on its children nodes (if any).
void Model::processNode(aiNode* node, const aiScene* scene)
{
	// process all the node's meshes (if any)
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		m_Meshes.push_back(processMesh(mesh, scene));
	}
	// then do the same for each of its children
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	// data to fill
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;
	Material m;

	// walk through each of the mesh's vertices
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		// we declare a placeholder vector since assimp uses its own vector class 
		// that doesn't directly convert to glm's vec3 class
		// so we transfer the data to this placeholder glm::vec3 first. // positions
		glm::vec3 vector;
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.position = vector;
		// normals
		if (mesh->HasNormals())
		{
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.normal = vector;
		}
		// texture coordinates
		if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
		{
			glm::vec2 vec;
			// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
			// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.texUV = vec;
		}
		else
			vertex.texUV = glm::vec2(0.0f, 0.0f);

		vertices.push_back(vertex);
	}
	// process indices / iterate through each mesh's face (every face here is a triangle of the mesh because we triangulated)
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	// process material
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		m = loadMaterial(material);

		// 1. diffuse maps
		std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "diffuseMap");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		// 2. specular maps
		std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "specularMap");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		// 3. normal maps
		std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "normalMap");
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
		// 4. height maps
		std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "heightMap");
		textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
	}
	Mesh mesh2(vertices, indices, textures);
	mesh2.setMaterial(m);
	return mesh2;
}

Material Model::loadMaterial(aiMaterial* mat) {
	Material material;
	aiColor3D color(0.f, 0.f, 0.f);
	float shininess;

	mat->Get(AI_MATKEY_COLOR_DIFFUSE, color);
	material.diffuse = glm::vec3(color.r, color.g, color.b);

	mat->Get(AI_MATKEY_COLOR_AMBIENT, color);
	material.ambient = glm::vec3(color.r, color.g, color.b);

	mat->Get(AI_MATKEY_COLOR_SPECULAR, color);
	material.specular = glm::vec3(color.r, color.g, color.b);

	mat->Get(AI_MATKEY_SHININESS, shininess);
	material.shininess = shininess;

	return material;
}


std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
	std::vector<Texture> textures;
	std::string filepath;

	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		bool skip = false;
		filepath = m_Directory + '/' + str.C_Str();
		for (unsigned int j = 0; j < textures_loaded.size(); j++)
		{
			if (std::strcmp(textures_loaded[j].m_FilePath.data(), filepath.c_str()) == 0)
			{
				textures.push_back(textures_loaded[j]);
				skip = true;
				break;
			}
		}
		if (!skip)
		{
			Texture texture;
			texture.LoadModelTexture(filepath, typeName);
			textures.push_back(texture);
			textures_loaded.push_back(texture);
		}
	}
	return textures;
}

Texture Model::TextureFromFile(const std::string& path, const std::string& type)
{
	std::string filename = std::string(path);

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return Texture(path, type);
}