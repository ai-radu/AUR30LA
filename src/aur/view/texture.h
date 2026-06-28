#pragma once
#include "glad/glad.h"
#include "stb_image.h"
#include "shader.h"

class Texture {
    public:
        unsigned int ID;
        GLenum type;
        Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);
        void texUnit(Shader& shader, const char* uniform, unsigned int unit);
        void Bind();
        void Unbind();
        void Delete();
};