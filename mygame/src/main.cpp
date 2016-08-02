// Local Headers
#include "glitter.hpp"

// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Standard Headers
#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;


/** A raw model
 *
*/
class RawModel
{
public:
    RawModel(int vaoId, int vertexCount) 
    {
        _vaoId = vaoId;
        _vertexCount = vertexCount;
    }

    int getVaoId(void)
    {
        return _vaoId;
    }

    int getVertexCount(void)
    {
        return _vertexCount;
    }

private:
    int _vaoId;
    int _vertexCount;
};


/** A raw model
 *
*/
class Loader
{
public:
    ~Loader()
    {
        for(auto vao: vaos)
        {
            glDeleteVertexArrays(1, &vao);
        }

        for(auto vbo: vbos)
        {
            glDeleteBuffers(1, &vbo);
        }
    }

    RawModel loadToVAO(vector<float> positions)
    {
        GLuint vaoId = createVAO();
        storeDataInAttributeList(0, positions);
        unbindVAO();
        return RawModel(vaoId, positions.size() / 3);
    }

private:

    vector<GLuint> vaos;
    vector<GLuint> vbos;

    GLuint createVAO()
    {
        GLuint vaoId;

        glGenVertexArrays(1, &vaoId);
        glBindVertexArray(vaoId);

        // Store reference for RAII
        vaos.push_back(vaoId);

        return vaoId;
    }

    /** What does this do?
     *
    */
    void storeDataInAttributeList(int attributeNumber, vector<float> buffer)
    {
        GLuint vboId;
        glGenBuffers(1, &vboId);

        glBindBuffer(GL_ARRAY_BUFFER, vboId);
        glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(float), &buffer[0], GL_STATIC_DRAW);
        glVertexAttribPointer(attributeNumber, 3, GL_FLOAT, false, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // Store reference for RAII
        vbos.push_back(vboId);
    }

    /** Unbind the currently bound VAO
    */
    void unbindVAO()
    {
        glBindVertexArray(0);
    }

};

class Renderer
{
public:
    /** Prepare OpenGL to render next frame
     *
    */
    void prepare()
    {
        glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void render(RawModel model)
    {
        glBindVertexArray(model.getVaoId());
        glEnableVertexAttribArray(0);
        glDrawArrays(GL_TRIANGLES, 0, model.getVertexCount());
        glDisableVertexAttribArray(0);
        glBindVertexArray(0);
    }

};

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

    Loader loader = Loader();
    Renderer renderer = Renderer();

    vector<float> vertices {
        // Left bottom triangle
        -0.5f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,

        // Right top triangle
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
    };

    RawModel model = loader.loadToVAO(vertices);

    // Rendering Loop
    while (glfwWindowShouldClose(mWindow) == false) {
        if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(mWindow, true);

        renderer.render(model);

        glfwSwapBuffers(mWindow);
        glfwPollEvents();
    }

    // loader.cleanup();
    glfwTerminate();

    return EXIT_SUCCESS;
}
