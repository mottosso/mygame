// Copyright 2016 <konstruktion@gmail.com>
#pragma once

#include <cstdio>
#include "glm/glm.hpp"
#include "GLFW/glfw3.h"

#include "util.hpp"


class Camera {
 public:
    Camera() : mPosition(glm::vec3(0, 0, 0)),
               mPitch(0),
               mYaw(0),
               mRoll(0) {}

    void move();

    glm::mat4 getViewMatrix();
    glm::vec3 getPosition() { return mPosition; }
    float getPitch() { return mPitch; }
    float getYaw() { return mYaw; }
    float getRoll() { return mRoll; }

 private:
    glm::vec3 mPosition;
    float mPitch;
    float mYaw;
    float mRoll;
};
