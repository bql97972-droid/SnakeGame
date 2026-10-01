#ifndef OBJECTS_H
#define OBJECTS_H

#include"bridge/bridge.h"
#include"src/core/world.h"

class object
{
	public:
		Bridge objectBridge1,objectBridge2;
		void create_object(float* vertices1,float* vertices2,unsigned int* indices);
		unsigned int return_objectBridge_VAO1();
		unsigned int return_objectBridge_VAO2();
		void delete_objectBridge();

		texture objectTexture1, objectTexture2;
		void load_object_texture(const char* path1, const char* path2);
		void set_object_texture(Shader& shader);
};
#endif 
