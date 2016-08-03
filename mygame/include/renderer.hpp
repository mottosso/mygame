#pragma once

#include "model.hpp"

/**
  * Main game renderer
  */
class Renderer
{
public:
    /**
      * Prepare OpenGL to render next frame
      */
    void prepare();

    /**
      * Render given model
      * @param model a VAO with a VBO
      */
    void render(TexturedModel texturedModel);
};
