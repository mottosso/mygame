// Copyright 2016 <konstruktion@gmail.com>
#include "util.hpp"

glm::mat4 Maths::createTransformationMatrix(glm::vec3 translation,
                                            float rx,
                                            float ry,
                                            float rz,
                                            float scale) {
    glm::mat4 matrix = glm::mat4();
    matrix = glm::translate(matrix, translation);
    matrix = glm::rotate(matrix, glm::radians(rx), glm::vec3(1, 0, 0));
    matrix = glm::rotate(matrix, glm::radians(ry), glm::vec3(0, 1, 0));
    matrix = glm::rotate(matrix, glm::radians(rz), glm::vec3(0, 0, 1));
    matrix = glm::scale(matrix, glm::vec3(scale, scale, scale));

    return matrix;
}
