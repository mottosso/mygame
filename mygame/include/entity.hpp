// Copyright 2016 <konstruktion@gmail.com>

#pragma once

#include "glm/glm.hpp"
#include "model.hpp"

// not using namespace glm due to shadowing member `scale`

class Entity {
 public:
    Entity(TexturedModel * model,
           glm::vec3 position,
           float rx,
           float ry,
           float rz,
           float scale) : mModel(model),
                          mPosition(position),
                          mRx(rx),
                          mRy(ry),
                          mRz(rz),
                          mScale(scale) {}

    void increasePosition(float dx, float dy, float dz);
    void increaseRotation(float dx, float dy, float dz);

    // Getters
    TexturedModel * getModel() { return mModel; }
    glm::vec3 getPosition() { return mPosition; }
    float getRx() { return mRx; }
    float getRy() { return mRy; }
    float getRz() { return mRz; }
    float getScale() { return mScale; }

 private:
    TexturedModel * mModel;
    glm::vec3 mPosition;
    float mRx, mRy, mRz;
    float mScale;
};
