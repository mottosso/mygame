// Copyright 2016 <konstruktion@gmail.com>

#pragma once

#include <cstdio>
#include <cstdlib>
#include <string>
#include <fstream>
#include <memory>  // unique_ptr

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"  // value_ptr
#include "glad/glad.h"

// TODO(marcus): Figure out how to control root directory
static const char* VERTEX_FILE = "../mygame/assets/shader.vert";
static const char* FRAGMENT_FILE = "../mygame/assets/shader.frag";


class ShaderProgram {
 public:
    explicit ShaderProgram(const char* vertexFname,
                           const char* fragmentFname);
    ~ShaderProgram();

    void use() { glUseProgram(mProgramId); }
    void forgo() { glUseProgram(0); }
    void bindAttribute(int attribute, const char * variableName);

    /**
     * Load shader from `fname` as `type`
     * @param fname a string argument, e.g. "myapp/shader.vert"
     * @param type an integer type, e.g. GL_VERTEX_SHADER
     */
    GLuint loadShader(const char * fname, int type);

    int getUniformLocation(const char * uniformName);
    void loadTransformationMatrix(glm::mat4 matrix);

    virtual void getAllUniformLocations();
    virtual void bindAttributes() {}

 protected:
    void loadFloat(GLuint location, float value);
    void loadVector(GLuint location, glm::vec3 value);
    void loadBoolean(GLuint location, bool value);
    void loadMatrix(GLuint location, glm::mat4 value);

 private:
    GLuint mProgramId;
    GLuint mVertexShaderId;
    GLuint mFragmentShaderId;
    GLint mStatus;
    GLint mLength;
    GLuint mTransformationMatrixLocation;
};


class StaticShader : public ShaderProgram {
 public:
    StaticShader() : ShaderProgram(VERTEX_FILE, FRAGMENT_FILE) {}

    virtual void bindAttributes();
};
