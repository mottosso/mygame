#pragma once

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <memory>  // unique_ptr

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>  // value_ptr
#include <glad/glad.h>

using namespace std;
using namespace glm;

// TODO(marcus): Figure out how to control root directory
static const string VERTEX_FILE = "../mygame/assets/shader.vert";
static const string FRAGMENT_FILE = "../mygame/assets/shader.frag";


class ShaderProgram
{
public:
    explicit ShaderProgram(string const & vertexFname, string const & fragmentFname);
    ~ShaderProgram();

    void use() { glUseProgram(mProgramId); }
    void forgo() { glUseProgram(0); }
    void bindAttribute(int attribute, const char * variableName);

    /**
     * Load shader from `fname` as `type`
     * @param fname a string argument, e.g. "myapp/shader.vert"
     * @param type an integer type, e.g. GL_VERTEX_SHADER
     */
    GLuint loadShader(const string & fname, int type);
    
    int getUniformLocation(const char * uniformName);
    void loadTransformationMatrix(mat4 matrix);

    virtual void getAllUniformLocations();
    virtual void bindAttributes() {};

protected:
    void loadFloat(GLuint location, float value);
    void loadVector(GLuint location, vec3 value);
    void loadBoolean(GLuint location, bool value);
    void loadMatrix(GLuint location, mat4 value);

private:
    GLuint mProgramId;
	GLuint mVertexShaderId;
	GLuint mFragmentShaderId;
	GLint mStatus;
	GLint mLength;
	GLuint mTransformationMatrixLocation;
};


class StaticShader : public ShaderProgram
{
public:
	StaticShader() : ShaderProgram(VERTEX_FILE, FRAGMENT_FILE) {};

	virtual void bindAttributes();
};