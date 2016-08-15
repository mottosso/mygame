// Copyright 2016 <konstruktion@gmail.com>

#pragma once

#include "model.hpp"
#include "entity.hpp"
#include "shader.hpp"

/**
 * Main game renderer
 */
class Renderer {
 public:
    /**
     * Prepare OpenGL to render next frame
     */
    void prepare();

    /**
     * Render given model
     * @param model a VAO with a VBO
     */
    void render(Entity * entity, StaticShader * shader);
    // void render(TexturedModel * texturedModel);
};
