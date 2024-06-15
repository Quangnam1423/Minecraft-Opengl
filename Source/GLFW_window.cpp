#include "GLFW_window.h"


//---------------------------------------------------------------------------------------
//preprocessor
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);


//----------------------------------------------------------------------------------------
/*
* contructor of engine class
*/
Window::Window(int _HEIGHT, int _WIDTH)
{

	glfwInit();

	this->SCR_HEIGHT = _HEIGHT;
	this->SCR_WIDTH = _WIDTH;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	this->window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Engine",
		NULL , NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	// set the callback function when window is resized
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwMakeContextCurrent(window);
	// loading opengl api
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}
	//---------------------------------------------------------------------------------------------
	// create shader program
	ourShader = new shader("Resource/Shader/vertex.shader" , "Resource/Shader/fragment.shader");
	//set prespective projection for shaderProgram
	ourShader->use();
	projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(70.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	ourShader->setMat4("projection", projection);
	view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	// pass transformation matrices to the shader
	ourShader->setMat4("view", view);
	//----------------------------------------------------------------------------------------------
	//load texture for shader program in gpu
	if (this->loadTexture("Resource/Texture/ozil.jpg"))
	{
		std::cout << "Load texture successfully!";
	}
	else
		std::cout << "fail to load texture!";
	//-----------------------------------------------------------------------------------------------
	// create VAO , VBO and EBO for storing buffers data in GPU's memory 
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// note that VAO is in use
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	//set attribute for the vertex attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	//unbind the buffer and vertex array when load status and vertice sucessfullly
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//-----------------------------------------------------------------------------------------------------
	//clear color for window swap buffers for next time to draw into screen
	glEnable(GL_DEPTH_TEST);
	glfwSwapBuffers(window);
}



/*
* destructor of engine class 
*/
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
	// while loop
	while (!glfwWindowShouldClose(window))
	{
		glfwSwapInterval(1); 
		// Giới hạn tốc độ khung hình theo v-sync

		//handle events
		//_____________	
		processInput(window);

		//Draw---------------------------------------------------------------------------
		Draw();
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

}


void Window::Draw()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//---------------------------------------------------------------------------------------
	glBindVertexArray(VAO);
	for (unsigned int i = 0; i < 10; i++)
	{
		// calculate the model matrix for each object and pass it to shader before drawing
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[i]);
		float angle = (float)glfwGetTime() * (i + 5) / (i + 3);
		model = glm::rotate(model, angle, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, angle, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, angle, glm::vec3(1.0f, 0.0f, 1.0f));
		ourShader->setMat4("model", model);

		glDrawElements(GL_TRIANGLES, 38, GL_UNSIGNED_INT, 0);
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


/*
* the function that determine when engine should be closed.
* 
*/

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}




void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}



