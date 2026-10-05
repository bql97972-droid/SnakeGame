#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<cstdlib> 
#include<vector>
#include<glm/glm.hpp>
#include"core/world.h"
#include"renderer/object.h"
#include"data/data.h"

void draw_object(Shader& shader, object& obj);
void processInput(GLFWwindow* window);
void set_cube_position(Shader& shader, glm::vec3 position);
void snake_game_logic(std::vector<glm::vec3>& snakePositions, Shader& shader, object& snake,
	GLFWwindow* window, glm::vec3& foodPos ,const float& stepInterval ,int& direction ,const float& mapMin,const float& mapMax ,float& timeSum);
glm::vec3 random_food_position(const std::vector<glm::vec3>& snakePositions);

float deltaTime = 0.0f;
float lastFrame = 0.0f;
float timeSum = 0.0f;
const float stepInterval = 1.0f; 

int direction = 0;
glm::vec3 foodPos;
std::vector<glm::vec3> snakePositions = { glm::vec3(0.45f, -0.35f, 0.55f) , glm::vec3(0.45f, -0.45f, 0.55f) };

const float mapMin = -0.45f;    
const float mapMax = 0.45f;      

int main()
{
	mywindow windowInstance;
	windowInstance.create_a_window();
	windowInstance.set_mode();
	Shader shader("res/shaders/basic.vert", "res/shaders/basic.frag");
	camera myCamera;
	
	object floor;
	floor.create_object(floor_up, floor_front, floor_right, floor_left, cube);
	floor.load_object_texture("res/textures/grass.jpg","res/textures/sideofgrass.jpg");
	
	object snake;
	snake.create_object(cube_up, cube_front, cube_right, cube_left, cube);
	snake.load_object_texture("res/textures/snakeup.png", "res/textures/snakefront.png");

	object food;
	food.create_object(cube_up, cube_front, cube_right, cube_left, cube);
	food.load_object_texture("res/textures/foodup.png", "res/textures/foodfront.png");

	shader.use();
	myCamera.set_camera(shader);
	floor.set_object_texture(shader);
	snake.set_object_texture(shader);
	food.set_object_texture(shader);

	srand(static_cast<unsigned int>(glfwGetTime() * 1000.0f)); 
	foodPos = random_food_position(snakePositions);            

	while (!glfwWindowShouldClose(windowInstance.window))
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		timeSum += deltaTime;

		glClearColor(0.52, 0.80, 0.92, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		processInput(windowInstance.window);
		
		set_cube_position(shader, glm::vec3(0.0f, 0.0f, 0.0f));
		draw_object(shader, floor);

		snake_game_logic(snakePositions, shader, snake, windowInstance.window , foodPos, stepInterval, direction, mapMin, mapMax, timeSum);
		for (std::vector<glm::vec3>::iterator it = snakePositions.begin(); it != snakePositions.end(); ++it)
		{
			set_cube_position(shader, *it);
			draw_object(shader, snake);
		}

		set_cube_position(shader, foodPos);
		draw_object(shader, food);


		glfwSwapBuffers(windowInstance.window);	
		glfwPollEvents();
	}

	floor.delete_objectBridge();
	snake.delete_objectBridge();
	food.delete_objectBridge();
	shader.delete_program();

	glfwTerminate();
	return 0;
}
