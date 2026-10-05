#ifndef WORLD_H
#define WORLD_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <string>
#include <glm/glm.hpp>

const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 1000;

class mywindow
{
	public:
		GLFWwindow* window;

		void create_a_window();
		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);//思考加1
		void set_mode();
};

class Shader
{
	public:
		unsigned int ID;

		Shader(const char* vertexPath, const char* fragmentPath);
		void use();

		void delete_program();

		void setMat4(const std::string& name, const glm::mat4& value) const;
		void setInt(const std::string& name, int value) const;
		
};

class camera
{
public:
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	
	camera() : cameraPos(glm::vec3(0.0f, -1.0f, 3.0f)), cameraFront(glm::normalize(glm::vec3(0.0f, 1.0f, -3.0f))), cameraUp(glm::vec3(0.0f, 1.0f, 0.0f)) {
	}
	void set_camera(Shader& shader); 
};

#endif