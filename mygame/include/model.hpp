#pragma once

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <glad/glad.h>

using namespace std;

/**
 * A raw model
 */
class RawModel
{
public:
    RawModel(int vaoId, int vertexCount)
        : _vaoId(vaoId), _vertexCount(vertexCount) {};

    int getVaoId(void) { return _vaoId; }
    int getVertexCount(void) { return _vertexCount; }

private:
    int _vaoId;
    int _vertexCount;
};


/**
 * A raw model
 */
class Loader
{
public:
    ~Loader();
    RawModel loadToVAO(vector<float> positions,
                       vector<float> textureCoords,
                       vector<int> indices);
    GLuint loadTexture(string const & fname);

private:

    vector<GLuint> vaos;
    vector<GLuint> vbos;
    vector<GLuint> textures;

    GLuint mTexture;

    GLuint createVAO();

    /**
     * What does this do?
     */
    void storeDataInAttributeList(int attributeNumber, int coordinateSize, vector<float> buffer);

    /**
     * Unbind the currently bound VAO
     */
    void unbindVAO() { glBindVertexArray(0); }
    void bindIndicesBuffer(vector<int> buffer);

};


class ModelTexture
{
public:
    ModelTexture(GLuint id)
        : _textureId(id) {};

    GLuint getId() { return _textureId; }

private:
    GLuint _textureId;
};

class TexturedModel
{
public:
    TexturedModel(RawModel model, ModelTexture texture)
        : _rawModel(model), _texture(texture) {};

    RawModel getRawModel() { return _rawModel; }
    ModelTexture getTexture() { return _texture; }

private:
    RawModel _rawModel;
    ModelTexture _texture;
};