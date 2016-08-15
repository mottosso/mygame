// Copyright 2016 <konstruktion@gmail.com>

#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glad/glad.h"


namespace Maths {
glm::mat4 createTransformationMatrix(glm::vec3 translation,
                                     float rx,
                                     float ry,
                                     float rz,
                                     float scale);

}  // namespace Maths
