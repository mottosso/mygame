// Copyright 2016 <konstruktion@gmail.com>
#include "shader.hpp"


GLuint ShaderProgram::loadShader(const char* fname, int type) {
    std::ifstream fd(fname, std::ios_base::in);

    if (!fd) {
        fprintf(stderr, "File did not exist: %s\n", fname);
        exit(EXIT_FAILURE);
    }

    auto src = std::string(std::istreambuf_iterator<char>(fd),
                           std::istreambuf_iterator<char>());

    const char * source = src.c_str();
    auto shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &mStatus);

    if (mStatus == false) {
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &mLength);
        std::unique_ptr<char[]> buffer(new char[mLength]);
        glGetShaderInfoLog(shader, mLength, nullptr, buffer.get());
        fprintf(stderr, "%s\n%s", fname, buffer.get());

        throw(std::string("Failed to load shader."));
    }

    glAttachShader(mProgramId, shader);
    glDeleteShader(shader);

    return mProgramId;
}


ShaderProgram::ShaderProgram(const char* vertexFname,
                             const char* fragmentFname) {
    mProgramId = glCreateProgram();

    mVertexShaderId = loadShader(vertexFname, GL_VERTEX_SHADER);
    mFragmentShaderId = loadShader(fragmentFname, GL_FRAGMENT_SHADER);

    bindAttributes();

    glLinkProgram(mProgramId);
    glValidateProgram(mProgramId);
    getAllUniformLocations();
}


ShaderProgram::~ShaderProgram() {
    forgo();

    for (auto id : { mVertexShaderId, mFragmentShaderId })
        glDetachShader(mProgramId, id);

    glDeleteProgram(mProgramId);
}


void ShaderProgram::bindAttribute(int attribute, const char * variableName) {
    glBindAttribLocation(mProgramId, attribute, variableName);
}


void StaticShader::bindAttributes() {
    bindAttribute(0, "position");
    bindAttribute(1, "textureCoords");
}


int ShaderProgram::getUniformLocation(const char * uniformName) {
    return glGetUniformLocation(mProgramId, uniformName);
}


void ShaderProgram::getAllUniformLocations() {
    mTransformationMatrixLocation = getUniformLocation("transformationMatrix");
    mProjectionMatrixLocation = getUniformLocation("projectionMatrix");
    mViewMatrixLocation = getUniformLocation("viewMatrix");
}


void ShaderProgram::loadFloat(GLuint location, float value) {
    glUniform1f(location, value);
}


void ShaderProgram::loadVector(GLuint location, glm::vec3 value) {
    glUniform3f(location, value.x, value.y, value.z);
}


void ShaderProgram::loadBoolean(GLuint location, bool value) {
    glUniform1f(location, value ? 1.0f: 0.0f);
}


void ShaderProgram::loadMatrix(GLuint location, glm::mat4 value) {
    glUniformMatrix4fv(location, 1, false, value_ptr(value));
}


void ShaderProgram::loadTransformationMatrix(glm::mat4 matrix) {
    loadMatrix(mTransformationMatrixLocation, matrix);
}


void ShaderProgram::loadProjectionMatrix(glm::mat4 matrix) {
    loadMatrix(mProjectionMatrixLocation, matrix);
}

void ShaderProgram::loadViewMatrix(glm::mat4 matrix) {
    loadMatrix(mViewMatrixLocation, matrix);
}
