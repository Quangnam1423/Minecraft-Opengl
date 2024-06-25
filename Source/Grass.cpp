#include "Grass.h"


void Grass::Draw(shader& ourShader)
{
	glBindVertexArray(VAO);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	ourShader.setMat4("model", model);
	ourShader.use();
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}