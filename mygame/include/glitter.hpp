// Preprocessor Directives
#pragma once

// System Headers
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// Reference: https://github.com/nothings/stb/blob/master/stb_image.h#L4
// To use stb_image, add this in *one* C++ source file.
//     #define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

// Define Some Constants
const int mWidth = 1280;
const int mHeight = 800;

#define SHADER_SOURCE(...) "#version 400 core\n"#__VA_ARGS__
#define STRINGIZE_SOURCE(...) #__VA_ARGS__