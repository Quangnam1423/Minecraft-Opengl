#include "GLFW_window.h"
#include <iomanip>



Window::Window(int _HEIGHT, int _WIDTH) : SCR_HEIGHT(_HEIGHT) , 
										  SCR_WIDTH(_WIDTH) , 
										  mousePos({(float)_HEIGHT / 2 ,(float)_WIDTH / 2}),
								          firstMouse(false) , deltaTime(0.0f) , lastFrame(0.0f)
{
	glfwInitialize();
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		return;

							// position                                                     worldUp                              look At 
	camera = new Camera(glm::vec3(0.0f , CHUNK_HEIGHT / 2 , CHUNK_SIZE), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	ourShader = new shader("Resource/Shader/vertex.shader" , "Resource/Shader/fragment.shader");
	
	_world = new World();
	ourShader->use();
	projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	ourShader->setMat4("projection", projection);
	view = glm::mat4(1.0f);
	view  = camera->GetViewMatrix();
	ourShader->setMat4("view", view);
	if (!loadTexture("Resource/Texture/blocks4.png")) { std::cout << "Can't load texture to GPU" << std::endl; }

	glfwSwapBuffers(window);
}

Window::~Window()
{


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
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
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
	projection = glm::perspective(glm::radians(camera->getZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 500.0f);
	ourShader->setMat4("projection", projection);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_world->Draw(*ourShader);
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
	{
		camera->ProcessKeyboard(JUMP, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
		camera->ProcessKeyboard(DOWN, deltaTime);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	Window* app = static_cast<Window*> (glfwGetWindowUserPointer(window));
	glViewport(0, 0, width, height);
	app->SCR_WIDTH = (float)width;
	app->SCR_HEIGHT = (float)height;
}

void mouse_callback(GLFWwindow* window,  double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);
	Window* app = static_cast<Window*> (glfwGetWindowUserPointer(window));

	if (app->getFirstMouse())
	{
		float xoffset = xpos - app->getMousePos().xPos;
		float yoffset = app->getMousePos().yPos - ypos;
		app->getCamera()->ProcessMouseMovement(xoffset, yoffset, true);
		app->setMousePos({ xpos , ypos });
	}
}


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	Window* app = static_cast<Window*> (glfwGetWindowUserPointer(window));
	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		app->setMousePos({ (float)xpos , (float)ypos });

		if (action == GLFW_PRESS)
		{
			app->setFirstMouse(true);
		}
		else if (action == GLFW_RELEASE)
		{
			app->setFirstMouse(false);
		}
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Window* app = static_cast<Window*> (glfwGetWindowUserPointer(window));
	app->getCamera()->ProcessMouseScroll(static_cast<float>(yoffset));
}
