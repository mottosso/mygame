// Copyright 2016 <konstruktion@gmail.com>
#include "camera.hpp"

extern GLFWwindow* gWindow;


void Camera::move() {
    if (glfwGetKey(gWindow, GLFW_KEY_W) == GLFW_PRESS) mPosition.z += 0.002f;
    if (glfwGetKey(gWindow, GLFW_KEY_A) == GLFW_PRESS) mPosition.x += 0.002f;
    if (glfwGetKey(gWindow, GLFW_KEY_S) == GLFW_PRESS) mPosition.z -= 0.002f;
    if (glfwGetKey(gWindow, GLFW_KEY_D) == GLFW_PRESS) mPosition.x -= 0.002f;
}


glm::mat4 Camera::getViewMatrix() {
    return Maths::createViewMatrix(mPosition, mPitch, mYaw);
}
