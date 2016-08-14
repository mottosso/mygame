#include "shader.hpp"


GLuint ShaderProgram::loadShader(string const & fname, int type)
{
    ifstream fd(fname, ios_base::in);

    if (!fd)
    {
        fprintf(stderr, "File did not exist: %s\n", fname.c_str());
        exit(EXIT_FAILURE);
    }

    auto src = string(istreambuf_iterator<char>(fd),
                      istreambuf_iterator<char>());

    const char * source = src.c_str();
    auto shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &mStatus);

    if (mStatus == false)
    {
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &mLength);
        unique_ptr<char[]> buffer(new char[mLength]);
        glGetShaderInfoLog(shader, mLength, nullptr, buffer.get());
        fprintf(stderr, "%s\n%s", fname.c_str(), buffer.get());

        throw(string("Failed to load shader."));
    }

    glAttachShader(mProgramId, shader);
    glDeleteShader(shader);

    return mProgramId;
}


ShaderProgram::ShaderProgram(string const & vertexFname, string const & fragmentFname)
{
    mProgramId = glCreateProgram();

    mVertexShaderId = loadShader(vertexFname, GL_VERTEX_SHADER);
    mFragmentShaderId = loadShader(fragmentFname, GL_FRAGMENT_SHADER);

    bindAttributes();

    glLinkProgram(mProgramId);
    glValidateProgram(mProgramId);
    getAllUniformLocations();
}


ShaderProgram::~ShaderProgram()
 {
    forgo();

    for(auto id: { mVertexShaderId, mFragmentShaderId })
        glDetachShader(mProgramId, id);

    glDeleteProgram(mProgramId);
}


void ShaderProgram::bindAttribute(int attribute, const char * variableName)
{
    glBindAttribLocation(mProgramId, attribute, variableName);
}


void StaticShader::bindAttributes()
{
    bindAttribute(0, "position");
    bindAttribute(1, "textureCoords");
}

    
int ShaderProgram::getUniformLocation(const char * uniformName)
{
    return glGetUniformLocation(mProgramId, uniformName);
}

void ShaderProgram::getAllUniformLocations()
{
    mTransformationMatrixLocation = getUniformLocation("transformationMatrix");
}


void ShaderProgram::loadFloat(GLuint location, float value)
{
    glUniform1f(location, value);
}


void ShaderProgram::loadVector(GLuint location, vec3 value)
{
    glUniform3f(location, value.x, value.y, value.z);
}


void ShaderProgram::loadBoolean(GLuint location, bool value)
{
    glUniform1f(location, value ? 1 : 0);
}


void ShaderProgram::loadMatrix(GLuint location, mat4 value)
{
    glUniformMatrix4fv(location, 1, false, value_ptr(value));
}

void ShaderProgram::loadTransformationMatrix(mat4 matrix)
{
    loadMatrix(mTransformationMatrixLocation, matrix);
}
