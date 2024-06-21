#include "GLFW_window.h"

// preprocessor
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

Window::Window(int _HEIGHT, int _WIDTH) : SCR_HEIGHT(_HEIGHT) , SCR_WIDTH(_WIDTH) ,  
										mousePos({ (float)_HEIGHT / 2 , (float)_WIDTH / 2}), 
										firstMouse(false), 
										deltaTime(0.0f), 
										lastFrame(0.0f)
{
	glfwInitialize();
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { return; }
	camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f) , glm::vec3(0.0f , 1.0f , 0.0f) , glm::vec3(0.0f , 0.0f , 0.0f));

	ourShader = new shader("Resource/Shader/1.model_loading.vs" , "Resource/Shader/1.model_loading.fs");
	ourShader->use();
	projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	ourShader->setMat4("projection", projection);
	view = glm::mat4(1.0f);
	view  = camera->GetViewMatrix();
	ourShader->setMat4("view", view);
		glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
	model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));	// it's a bit too big for our scene, so scale it down
	ourShader->setMat4("model", model);// it's a bit too big for our scene, so scale it down
	ourModel = new Model("D:/backpack/backpack.obj");

	//if (!loadTexture("Resource/Texture/ozil.jpg")) { std::cout << "Can't load texture to GPU" << std::endl; }
	////-----------------------------------------------------------------------------------------------
	//// create VAO , VBO and EBO for storing buffers data in GPU's memory 
	//glGenVertexArrays(1, &VAO);
	//glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);
	//// note that VAO is in use
	//glBindVertexArray(VAO);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	////set attribute for the vertex attribute
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	//glEnableVertexAttribArray(2);
	////unbind the buffer and vertex array when load status and vertice sucessfullly
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);
	////glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	////-----------------------------------------------------------------------------------------------------
	////clear color for window swap buffers for next time to draw into screen
	////glEnable(GL_CULL_FACE);
	////glCullFace(GL_FRONT);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	//glFrontFace(GL_CW);
	glEnable(GL_DEPTH_TEST);
	glfwSwapBuffers(window);
}

Window::~Window()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	delete ourShader;

	glfwDestroyWindow(window);
	glfwTerminate();
	std::cout << "Destructor: Memory deallocated" << std::endl;
}

void Window::run()
{
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwSwapInterval(1); 
		processInput();
		Draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

}

bool Window::loadTexture(std::string name)
{
	unsigned int texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(name.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
		return false;
	}
	stbi_image_free(data);
	ourShader->use();
	ourShader->setInt("texture", 0);
	return true;
}

void Window::Draw()
{
	view = camera->GetViewMatrix();
	ourShader->setMat4("view", view);
	projection = glm::perspective(glm::radians(camera->getZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	ourShader->setMat4("projection", projection);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//---------------------------------------------------------------------------------------
	glBindVertexArray(VAO);
	//for (unsigned int i = 0; i < cubePositions.size() ; i++)
	//{
	//	// calculate the model matrix for each object and pass it to shader before drawing
	glm::mat4 model = glm::mat4(1.0f);
	float angle = (float)glfwGetTime() * (10 + 5) / (10 + 3);
	//model = glm::rotate(model, angle, glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, angle, glm::vec3(0.0f, 1.0f, 0.0f));
	//model = glm::rotate(model, angle, glm::vec3(1.0f, 0.0f, 1.0f));
	ourShader->setMat4("model", model);

	//	glDrawElements(GL_TRIANGLES, 38, GL_UNSIGNED_INT, 0);
	//}


	ourModel->Draw(*ourShader);
}

void Window::glfwInitialize() 
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	this->window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Engine",
		NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwMakeContextCurrent(window);
	glfwSetWindowUserPointer(window, this);
}

void Window::processInput()
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		camera->ProcessKeyboard(JUMP, deltaTime);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window,  double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);
	Window* app = static_cast<Window*> (glfwGetWindowUserPointer(window));

	if (app->firstMouse == true)
	{
		float xoffset = xpos - app->mousePos.xpos;
		float yoffset = app->mousePos.ypos - ypos;
		app->camera->ProcessMouseMovement(xoffset, yoffset, true);
		app->mousePos = mousePosition(xpos, ypos);
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Window* app = static_cast<Window*> (glfwGetWindowUserPointer(window));
	app->camera->ProcessMouseScroll(static_cast<float>(yoffset));
}


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	Window* app = static_cast<Window*> (glfwGetWindowUserPointer(window));
	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		if (action == GLFW_PRESS)
		{
			app->mousePos = mousePosition((float)xpos, (float)ypos);
			app->firstMouse = true;
		}
		else if (action == GLFW_RELEASE)
		{
			app->firstMouse = false;
		}
	}
}