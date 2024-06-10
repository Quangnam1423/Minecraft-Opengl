#include "GLFW_window.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);



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

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

//---------------------------------------------------------------------------------
	ourShader = new shader("Resource/Shader/vertex.shader" , "Resource/Shader/fragment.shader");

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

	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6* sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	//unbind the buffer and vertex array when load status and vertice sucessfullly
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//Glad: load all function pointers 
	//________________________________
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
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

		//draw the monitor
		//_______________
		glClearColor(0.2f, 0.7f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//draw all the vertex
		ourShader->use();
		glBindVertexArray(VAO); 
		glDrawElements(GL_TRIANGLES, 9 , GL_UNSIGNED_INT , 0);


		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

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

