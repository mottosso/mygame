// Copyright 2016 <konstruktion@gmail.com>
#include "entity.hpp"


void Entity::increasePosition(float dx, float dy, float dz) {
    mPosition.x += dx;
    mPosition.y += dy;
    mPosition.z += dz;
}

void Entity::increaseRotation(float dx, float dy, float dz) {
    mRx += dx;
    mRy += dy;
    mRz += dz;
}
