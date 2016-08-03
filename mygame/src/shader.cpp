#include "shader.hpp"

using namespace std;


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
}


ShaderProgram::~ShaderProgram()
 {
    forgo();

    for(auto id: { mVertexShaderId, mFragmentShaderId })
        glDetachShader(mProgramId, id);

    glDeleteProgram(mProgramId);
}


void ShaderProgram::bindAttribute(int attribute, string variableName)
{
    glBindAttribLocation(mProgramId, attribute, variableName.c_str());
}


void StaticShader::bindAttributes()
{
    bindAttribute(0, "position");
    bindAttribute(1, "textureCoords");
}