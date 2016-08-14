#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>

using namespace glm;


class Maths
{
public:
	mat4 createTransformationMatrix(vec3 translation,
									float rx,
									float ry,
									float rz,
									float sz);
};
