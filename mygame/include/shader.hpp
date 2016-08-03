#pragma once

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <memory>  // unique_ptr

#include <glad/glad.h>

using namespace std;

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
    void bindAttribute(int attribute, string variableName);
    virtual void bindAttributes() {};

    /**
     * Load shader from `fname` as `type`
     * @param fname a string argument, e.g. "myapp/shader.vert"
     * @param type an integer type, e.g. GL_VERTEX_SHADER
     */
    GLuint loadShader(const string & fname, int type);

private:
    GLuint mProgramId;
	GLuint mVertexShaderId;
	GLuint mFragmentShaderId;
	GLint mStatus;
	GLint mLength;

};


class StaticShader : public ShaderProgram
{
public:
	StaticShader() : ShaderProgram(VERTEX_FILE, FRAGMENT_FILE) {};

	virtual void bindAttributes();
};