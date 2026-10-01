#ifndef BRIDGE_H
#define BRIDGE_H

class Bridge
{
public:
    unsigned int VAO, VBO, IBO;
    void cpu_to_gpu(float* vertices, unsigned int* indices);
    ~Bridge();
};

#endif // BRIDGE_H
