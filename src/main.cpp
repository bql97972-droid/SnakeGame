#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include"renderer/shader.h"
#include"renderer/bridge.h"
#include"renderer/loadtexture.h"

void processInput(GLFWwindow* window);
GLFWwindow* create_a_window();
unsigned int load_texture(const char* path);
void set_world(Shader& shader);

int main()
{
	GLFWwindow* window = create_a_window();
	glEnable(GL_DEPTH_TEST);
	Shader shader("res/shaders/basic.vert", "res/shaders/basic.frag");

	float floorVerticesup[] = {
		// positions          // color coords          // texture coords
		 0.8f, -0.8f,  0.0f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
		-0.8f, -0.8f,  0.0f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
		-0.8f,  0.8f,  0.0f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
		 0.8f,  0.8f,  0.0f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
	};
	unsigned int floorIndicesup[] = {
		0, 1, 2,
		0, 2, 3
	};

	float floorVerticesfront[] = {
		// positions          // color coords          // texture coords
		 0.8f, -0.8f,  0.0f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
		 0.8f, -0.8f, -0.8f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
		-0.8f, -0.8f, -0.8f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
		-0.8f, -0.8f,  0.0f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
	};
	unsigned int floorIndicesfront[] = {
		0, 1, 2,
		0, 2, 3
	};

	Bridge floorupBridge;
	floorupBridge.cpu_to_gpu(floorVerticesup, floorIndicesup);
	loadtexture floorTextureup;
	floorTextureup.load("C:/SnakeGame/res/textures/grass.jpg");
	shader.setInt("ourTexture", floorTextureup.textureID);

	Bridge floorFrontBridge;
	floorFrontBridge.cpu_to_gpu(floorVerticesfront, floorIndicesfront);
	loadtexture floorTexturefront;
	floorTexturefront.load("C:/SnakeGame/res/textures/sideofgrass.jpg");
	shader.setInt("ourTexture", floorTexturefront.textureID);


	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.52, 0.80, 0.92, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		processInput(window);

		shader.use();

		set_world(shader);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, floorTextureup.textureID);
		glBindVertexArray(floorupBridge.VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, floorTexturefront.textureID);
		glBindVertexArray(floorFrontBridge.VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);	
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}