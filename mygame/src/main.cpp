// Copyright 2016 <konstruktion@gmail.com>

// Standard Headers
#include <cstdio>
#include <cstdlib>
#include <vector>

// System Headers
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/gtx/string_cast.hpp"  // string_cast

GLFWwindow* gWindow;

// Local Headers
#include "glitter.hpp"
#include "camera.hpp"
#include "shader.hpp"
#include "model.hpp"
#include "renderer.hpp"
#include "entity.hpp"


int main(void) {
    // Load GLFW and Create a Window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    gWindow = glfwCreateWindow(mWidth, mHeight, "OpenGL", nullptr, nullptr);

    // Check for Valid Context
    if (gWindow == nullptr) {
        fprintf(stderr, "Failed to Create OpenGL Context");
        return EXIT_FAILURE;
    }

    // Create Context and Load OpenGL Functions
    glfwMakeContextCurrent(gWindow);
    gladLoadGL();

    fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));

    std::vector<float> vertices = {
        -0.5f, 0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,

        -0.5f, 0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,

        0.5f, 0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,

        -0.5f, 0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,

        -0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, 0.5f,

        -0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, 0.5f
    };

    std::vector<float> textureCoords = {
        0, 0,
        0, 1,
        1, 1,
        1, 0,
        0, 0,
        0, 1,
        1, 1,
        1, 0,
        0, 0,
        0, 1,
        1, 1,
        1, 0,
        0, 0,
        0, 1,
        1, 1,
        1, 0,
        0, 0,
        0, 1,
        1, 1,
        1, 0,
        0, 0,
        0, 1,
        1, 1,
        1, 0
    };

    std::vector<int> indices = {
        0, 1, 3,
        3, 1, 2,
        4, 5, 7,
        7, 5, 6,
        8, 9, 11,
        11, 9, 10,
        12, 13, 15,
        15, 13, 14,
        16, 17, 19,
        19, 17, 18,
        20, 21, 23,
        23, 21, 22
    };

    Loader loader = Loader();
    StaticShader shader = StaticShader();
    Renderer renderer = Renderer(&shader);

    RawModel model = loader.loadToVAO(&vertices, &textureCoords, &indices);
    ModelTexture texture = ModelTexture(
        loader.loadTexture("../mygame/assets/texture.jpg"));
    TexturedModel texturedModel = TexturedModel(&model, &texture);

    Entity entity = Entity(&texturedModel,
                           glm::vec3(0, 0, -5),  // Translate
                           0, 0, 0,              // Rotation
                           1);                   // Scale

    Camera camera = Camera();

    // Rendering Loop
    while (glfwWindowShouldClose(gWindow) == false) {
        if (glfwGetKey(gWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(gWindow, true);

        entity.increaseRotation(0, 0.1f, 0);

        camera.move();

        renderer.prepare();

        shader.use();
        shader.loadViewMatrix(camera.getViewMatrix());
        renderer.render(&entity, &shader);
        shader.forgo();

        glfwSwapBuffers(gWindow);
        glfwPollEvents();
    }

    glfwTerminate();

    return EXIT_SUCCESS;
}
