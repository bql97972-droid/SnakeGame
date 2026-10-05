#include "../core/world.h"
#include "object.h"
#include "bridge/bridge.h"
#include<glm/gtc/matrix_transform.hpp>
#include<vector>

void draw_object(Shader& shader, object& obj)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, obj.objectTexture1.textureID);
	glBindVertexArray(obj.return_objectBridge_VAO1());
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, obj.objectTexture2.textureID);
	glBindVertexArray(obj.return_objectBridge_VAO2());
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, obj.objectTexture2.textureID);
	glBindVertexArray(obj.return_objectBridge_VAO3());
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, obj.objectTexture2.textureID);
	glBindVertexArray(obj.return_objectBridge_VAO4());
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}
void set_cube_position(Shader& shader, glm::vec3 position)
{
	shader.setMat4("model", glm::translate(glm::mat4(1.0f), position));
}
glm::vec3 random_food_position(const std::vector<glm::vec3>& snakePositions)
{
	glm::vec3 pos;
	bool onSnake;
	do
	{
		int ix = rand() % 10;
		int iy = rand() % 10;
		pos = glm::vec3(-0.45f + ix * 0.1f, -0.45f + iy * 0.1f, 0.55f);
		onSnake = false;
		for (std::vector<glm::vec3>::const_iterator it = snakePositions.begin(); it != snakePositions.end(); ++it)
		{
			if (*it == pos) { onSnake = true; break; }
		}
	} while (onSnake);
	return pos;
}
void snake_game_logic(std::vector<glm::vec3>& snakePositions, Shader& shader, object& snake,
	GLFWwindow* window, glm::vec3& foodPos, const float& stepInterval, int& direction, const float& mapMin, const float& mapMax ,float& timeSum)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) direction = 1;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) direction = 2;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) direction = 3;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) direction = 4;

	if (direction != 0 && timeSum >= stepInterval)
	{
		glm::vec3 newHead = snakePositions[0];
		if (direction == 1)      newHead.y += 0.1f;
		else if (direction == 2) newHead.y -= 0.1f;
		else if (direction == 3) newHead.x -= 0.1f;
		else if (direction == 4) newHead.x += 0.1f;

		bool inside = (newHead.x >= mapMin && newHead.x <= mapMax &&
			newHead.y >= mapMin && newHead.y <= mapMax);

		if (inside)
		{
			bool ate = (glm::distance(newHead, foodPos) < 0.001f); // 容差判定，避免浮点误差导致吃不到（新思考2）

			if (!ate)
			{
				snakePositions.pop_back();
				snakePositions.insert(snakePositions.begin(), newHead);
				timeSum -= stepInterval;
			}
			if (ate)
			{
				snakePositions.insert(snakePositions.begin(), foodPos);
				foodPos = random_food_position(snakePositions);

			}
		}
	}
}
