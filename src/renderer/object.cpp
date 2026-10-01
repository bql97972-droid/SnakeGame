#include"object.h"

void object::create_object(float* vertices1,float* vertices2,unsigned int* indices)
{
	objectBridge1.cpu_to_gpu(vertices1, indices);
	objectBridge2.cpu_to_gpu(vertices2, indices);
}
unsigned int object::return_objectBridge_VAO1()
{
	return objectBridge1.VAO;
}
unsigned int object::return_objectBridge_VAO2()
{
	return objectBridge2.VAO;
}
void object::delete_objectBridge()
{
	objectBridge1.delete_buffers();
	objectBridge2.delete_buffers();
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