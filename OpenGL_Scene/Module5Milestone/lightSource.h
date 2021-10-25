#ifndef LIGHT_SOURCE_H
#define LIGHT_SOURCE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "GLmesh.h"

// GLM Math Header inclusions
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Light
{
public:
	Light(GLMesh& mesh);

	void transformation(GLint modelLoc, glm::vec3 gLightPosition, glm::vec3 gLightScale);
	void destroyMesh(GLMesh& mesh);
};


#endif