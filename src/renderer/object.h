
#ifndef OBJECTS_H
#define OBJECTS_H

#include"bridge/bridge.h"
#include"../core/world.h"

class object
{    

	public:
		Bridge objectBridge1,objectBridge2,objectBridge3,objectBridge4;
		void create_object(float* vertices1,float* vertices2,float* vertices3,float* vertices4,unsigned int* indices);
		unsigned int return_objectBridge_VAO1();
		unsigned int return_objectBridge_VAO2();
		unsigned int return_objectBridge_VAO3();
		unsigned int return_objectBridge_VAO4();
		void delete_objectBridge();

		texture objectTexture1, objectTexture2;
		void load_object_texture(const char* path1, const char* path2);
		void set_object_texture(Shader& shader);
};
#endif 
