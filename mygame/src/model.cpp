
// Reference: https://github.com/nothings/stb/blob/master/stb_image.h#L4
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "model.hpp"

#include <fstream>
#include <cstring>


RawModel Loader::loadToVAO(vector<float> positions,
                           vector<float> textureCoords,
                           vector<int> indices)
{
    GLuint vaoId = createVAO();
    bindIndicesBuffer(indices);

    storeDataInAttributeList(0, 3, positions);
    storeDataInAttributeList(1, 2, textureCoords);

    unbindVAO();
    return RawModel(vaoId, indices.size());
}

GLuint Loader::loadTexture(string const & fname)
{
    int w, h, comp;
    unsigned char * image = stbi_load(fname.c_str(), &w, &h, &comp, STBI_rgb);

    if (image == nullptr)
    {
        throw(string("Failed to load texture."));
    }

    // Debug info
    printf("size: %i\nw: %i\nh: %i\ncomp: %i", strlen((const char *) image), w, h, comp);

    glGenTextures(1, &mTexture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Upload texture to GPU
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    stbi_image_free(image);

    textures.push_back(mTexture);

    return mTexture;
}


Loader::~Loader()
{
    for(auto vao: vaos)
    {
        glDeleteVertexArrays(1, &vao);
    }

    for(auto vbo: vbos)
    {
        glDeleteBuffers(1, &vbo);
    }

    for(auto texture : textures)
    {
        glDeleteTextures(1, &texture);
    }
}


GLuint Loader::createVAO()
{
    GLuint vaoId;

    glGenVertexArrays(1, &vaoId);
    glBindVertexArray(vaoId);

    // Store reference for RAII
    vaos.push_back(vaoId);

    return vaoId;
}


void Loader::storeDataInAttributeList(int attributeNumber,
                                      int coordinateSize,
                                      vector<float> buffer)
{
    GLuint vboId;
    glGenBuffers(1, &vboId);

    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER,
                 buffer.size() * sizeof(float),
                 &buffer[0],
                 GL_STATIC_DRAW);
    glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, false, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Store reference for RAII
    vbos.push_back(vboId);
}


void Loader::bindIndicesBuffer(vector<int> buffer)
{
    GLuint vboId;
    glGenBuffers(1, &vboId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 buffer.size() * sizeof(float),
                 &buffer[0],
                 GL_STATIC_DRAW);
}
