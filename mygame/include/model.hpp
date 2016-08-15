// Copyright 2016 <konstruktion@gmail.com>

#pragma once

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>

#include "glad/glad.h"

/**
 * A raw model
 */
class RawModel {
 public:
    RawModel(int vaoId, int vertexCount)
        : mVaoId(vaoId), mVertexCount(vertexCount) {}

    int getVaoId(void) { return mVaoId; }
    int getVertexCount(void) { return mVertexCount; }

 private:
    int mVaoId;
    int mVertexCount;
};


/**
 * A raw model
 */
class Loader {
 public:
    ~Loader();
    RawModel loadToVAO(std::vector<float> * positions,
                       std::vector<float> * textureCoords,
                       std::vector<int> * indices);
    GLuint loadTexture(const char* fname);

 private:
    std::vector<GLuint> mVaos;
    std::vector<GLuint> mVbos;
    std::vector<GLuint> mTextures;

    GLuint mTexture;

    GLuint createVAO();

    /**
     * What does this do?
     */
    void storeDataInAttributeList(int attributeNumber, int coordinateSize,
                                  std::vector<float> * buffer);

    /**
     * Unbind the currently bound VAO
     */
    void unbindVAO() { glBindVertexArray(0); }
    void bindIndicesBuffer(std::vector<int> * buffer);
};


class ModelTexture {
 public:
    explicit ModelTexture(GLuint id)
        : mTextureId(id) {}

    GLuint getId() { return mTextureId; }

 private:
    GLuint mTextureId;
};

class TexturedModel {
 public:
    TexturedModel(RawModel * model, ModelTexture * texture)
        : mRawModel(model), mTexture(texture) {}

    RawModel * getRawModel() { return mRawModel; }
    ModelTexture * getTexture() { return mTexture; }

 private:
    RawModel * mRawModel;
    ModelTexture * mTexture;
};
