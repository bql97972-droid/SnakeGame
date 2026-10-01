#include<glad/glad.h>
#include<GLFW/glfw3.h>  
#include<iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include"shader.h"

glm::vec3 cameraPos = glm::vec3(0.0f, -1.0f, 3.0f);
glm::vec3 cameraFront = glm::normalize(glm::vec3(0.0f, 1.0f, -3.0f));
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

void set_world(Shader& shader)
{
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	shader.setMat4("model", model);

	glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	shader.setMat4("view", view);

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 800.0f, 0.1f, 100.0f);
	shader.setMat4("projection", projection);
}
