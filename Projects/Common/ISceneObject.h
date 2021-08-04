#ifndef ISCENEOBJECT_INTERFACE_H
#define ISCENEOBJECT_INTERFACE_H

#include <glm/glm.hpp>
#include "IMesh.h"

class ISceneObject
{
public:
	glm::mat4 m_Model;

	std::vector<std::shared_ptr<Light>> lightSources;

	//virtual void rotate(IMesh& around = this, glm::vec3& eulerAngles = glm::vec3(0.0)) = 0;
	virtual void translate(glm::mat4& around, glm::vec3& eulerAngles) = 0;
	virtual void rotate(glm::mat4& around, glm::vec3& eulerAngles) = 0;
	virtual void scale(glm::mat4& around, glm::vec3& eulerAngles) = 0;

	virtual glm::mat4& getModelMatrix() = 0;
};

#endif