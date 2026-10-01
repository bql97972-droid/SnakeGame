#ifndef BRIDGE_H
#define BRIDGE_H

class texture
{
    public:
        unsigned int textureID;
        void load_texture(const char* path);
};

class Bridge
{
    public:
        unsigned int VAO, VBO, IBO;
        void cpu_to_gpu(float* vertices, unsigned int* indices);
		void delete_buffers();
};
#endif