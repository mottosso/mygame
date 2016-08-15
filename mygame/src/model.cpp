// Copyright 2016 <konstruktion@gmail.com>

#include <fstream>
#include <cstring>

// Reference: https://github.com/nothings/stb/blob/master/stb_image.h#L4
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include "model.hpp"


RawModel Loader::loadToVAO(std::vector<float> * positions,
                           std::vector<float> * textureCoords,
                           std::vector<int> * indices) {
    GLuint vaoId = createVAO();
    bindIndicesBuffer(indices);

    storeDataInAttributeList(0, 3, positions);
    storeDataInAttributeList(1, 2, textureCoords);

    unbindVAO();
    return RawModel(vaoId, indices->size());
}

GLuint Loader::loadTexture(const char* fname) {
    int w, h, comp;
    unsigned char * image = stbi_load(fname, &w, &h, &comp, STBI_rgb);

    if (image == nullptr) {
        throw(std::string("Failed to load texture."));
    }

    // Debug info
    printf("size: %i\nw: %i\nh: %i\ncomp: %i",
           strlen((const char *) image), w, h, comp);

    glGenTextures(1, &mTexture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Upload texture to GPU
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image);
    stbi_image_free(image);

    mTextures.push_back(mTexture);

    return mTexture;
}


Loader::~Loader() {
    for (auto vao : mVaos) {
        glDeleteVertexArrays(1, &vao);
    }

    for (auto vbo : mVbos) {
        glDeleteBuffers(1, &vbo);
    }

    for (auto texture : mTextures) {
        glDeleteTextures(1, &texture);
    }
}


GLuint Loader::createVAO() {
    GLuint vaoId;

    glGenVertexArrays(1, &vaoId);
    glBindVertexArray(vaoId);

    // Store reference for RAII
    mVaos.push_back(vaoId);

    return vaoId;
}


void Loader::storeDataInAttributeList(int attributeNumber,
                                      int coordinateSize,
                                      std::vector<float> * buffer) {
    GLuint vboId;
    glGenBuffers(1, &vboId);

    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER,
                 buffer->size() * sizeof(float),
                 buffer->data(),
                 GL_STATIC_DRAW);
    glVertexAttribPointer(attributeNumber, coordinateSize,
                          GL_FLOAT, false, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Store reference for RAII
    mVbos.push_back(vboId);
}


void Loader::bindIndicesBuffer(std::vector<int> * buffer) {
    GLuint vboId;
    glGenBuffers(1, &vboId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 buffer->size() * sizeof(float),
                 buffer->data(),
                 GL_STATIC_DRAW);
}
