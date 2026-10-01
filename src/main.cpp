#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include"core/world.h"
#include"renderer/bridge/bridge.h"

void set_floor(Shader& shader);

int main()
{
	mywindow windowInstance;
	windowInstance.create_a_window();
	windowInstance.set_mode();
	Shader shader("res/shaders/basic.vert", "res/shaders/basic.frag");
	camera myCamera;

	set_floor(shader);
	

	while (!glfwWindowShouldClose(windowInstance.window))
	{
		glClearColor(0.52, 0.80, 0.92, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		windowInstance.processInput(windowInstance.window);

		shader.use();

		myCamera.set_camera(shader);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, floorTextureup.textureID);
		glBindVertexArray(floorupBridge.VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, floorTexturefront.textureID);
		glBindVertexArray(floorFrontBridge.VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(windowInstance.window);	
		glfwPollEvents();
	}

	floorFrontBridge.delete_buffers();
	floorupBridge.delete_buffers();
	shader.delete_program();

	glfwTerminate();
	return 0;
}
