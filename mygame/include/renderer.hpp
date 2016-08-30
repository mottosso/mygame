// Copyright 2016 <konstruktion@gmail.com>

#pragma once

#include "model.hpp"
#include "entity.hpp"
#include "shader.hpp"

static float FOV = 70.0f;
static float NEAR_PLANE = 0.1f;
static float FAR_PLANE = 1000.0f;

/**
 * Main game renderer
 */
class Renderer {
 public:
    /**
     * This only ever needs to happen once
    */
    explicit Renderer(StaticShader* shader);

    /**
    /**
     * Prepare OpenGL to render next frame
     */
    void prepare();

    /**
     * Render given model
     * @param model a VAO with a VBO
     */
    void render(Entity * entity, StaticShader * shader);
};
