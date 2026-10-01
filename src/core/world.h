#ifndef WORLD_H
#define WORLD_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <string>
#include <glm/glm.hpp>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

class mywindow
{
	public:
		GLFWwindow* window;

		GLFWwindow* create_a_window();
		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);//思考加1
		void set_mode();
		void processInput(GLFWwindow* window);
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
	glm::mat4 cube_model;

	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;

	camera(glm::vec3 pos, glm::vec3 front, glm::vec3 up)
		: cameraPos(pos), cameraFront(front), cameraUp(up) {
	}
	camera() : cameraPos(glm::vec3(0.0f, -1.0f, 3.0f)), cameraFront(glm::normalize(glm::vec3(0.0f, 1.0f, -3.0f))), cameraUp(glm::vec3(0.0f, 1.0f, 0.0f)) {
	}
	void set_cube_position(glm::vec3 position);
	void set_camera(Shader& shader); 
};
#endif