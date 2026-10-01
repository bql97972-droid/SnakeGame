#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>

class Shader
{
    public:
        unsigned int ID;
        Shader(const char* vertexPath, const char* fragmentPath);
        void use();
        void setMat4(const std::string& name, const glm::mat4& value) const;
        void setInt(const std::string& name, int value) const;
        ~Shader();
};

#endif // SHADER_H