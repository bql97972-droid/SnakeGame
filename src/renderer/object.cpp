#include "object.h"
#include "../core/world.h"    // 如果从 renderer 目录引用 core/world.h 的相对路径
#include "bridge/bridge.h"    // 如果 object.cpp 使用 Bridge/texture 的实现

class Shader;

void object::create_object(float* vertices1,float* vertices2,float* vertices3,float* vertices4,unsigned int* indices)
{
	objectBridge1.cpu_to_gpu(vertices1, indices);
	objectBridge2.cpu_to_gpu(vertices2, indices);
	objectBridge3.cpu_to_gpu(vertices3, indices);
	objectBridge4.cpu_to_gpu(vertices4, indices);
}
unsigned int object::return_objectBridge_VAO1()
{
	return objectBridge1.VAO;
}
unsigned int object::return_objectBridge_VAO2()
{
	return objectBridge2.VAO;
}
unsigned int object::return_objectBridge_VAO3()
{
	return objectBridge3.VAO;
}
unsigned int object::return_objectBridge_VAO4()
{
	return objectBridge4.VAO;
}
void object::delete_objectBridge()
{
	objectBridge1.delete_buffers();
	objectBridge2.delete_buffers();
	objectBridge3.delete_buffers();
	objectBridge4.delete_buffers();
}

void object::load_object_texture(const char* path1,const char* path2)
{
	objectTexture1.load_texture(path1);
	objectTexture2.load_texture(path2);
}
void object::set_object_texture(Shader& shader)
{
	shader.setInt("texture1", objectTexture1.textureID);
	shader.setInt("texture2", objectTexture2.textureID);
}