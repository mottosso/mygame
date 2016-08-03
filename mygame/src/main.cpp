
// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Standard Headers
#include <cstdio>
#include <cstdlib>
#include <vector>

// Local Headers
#include "glitter.hpp"
#include "shader.hpp"
#include "model.hpp"
#include "renderer.hpp"

using namespace std;


int main(void)
{
    // Load GLFW and Create a Window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    auto mWindow = glfwCreateWindow(mWidth, mHeight, "OpenGL", nullptr, nullptr);

    // Check for Valid Context
    if (mWindow == nullptr)
    {
        fprintf(stderr, "Failed to Create OpenGL Context");
        return EXIT_FAILURE;
    }

    // Create Context and Load OpenGL Functions
    glfwMakeContextCurrent(mWindow);
    gladLoadGL();

    fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));

    vector<float> vertices {
        -0.5f,  0.5f,  0.0f,
        -0.5f, -0.5f,  0.0f,
         0.5f, -0.5f,  0.0f,
         0.5f,  0.5f,  0.0f,
    };

    vector<float> textureCoords {
        0, 0,
        0, 1,
        1, 1,
        1, 0
    };

    vector<int> indices {
        0, 1, 3,
        3, 1, 2
    };

    Loader loader = Loader();
    Renderer renderer = Renderer();
    StaticShader shader = StaticShader();
    RawModel model = loader.loadToVAO(vertices, textureCoords, indices);
    ModelTexture texture = ModelTexture(loader.loadTexture("../mygame/assets/texture.jpg"));
    TexturedModel texturedModel = TexturedModel(model, texture);

    // Rendering Loop
    while (glfwWindowShouldClose(mWindow) == false) {
        if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(mWindow, true);

        renderer.prepare();

        shader.use();
        renderer.render(texturedModel);
        shader.forgo();

        glfwSwapBuffers(mWindow);
        glfwPollEvents();
    }

    // loader.cleanup();
    glfwTerminate();

    return EXIT_SUCCESS;
}
