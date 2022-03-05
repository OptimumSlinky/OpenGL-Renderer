#include "Framework.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void ProcessUserInput(GLFWwindow* window);

int main()
{
	// Initialize GLFW and designate OpenGL 3.3 and core-profile configuration
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window object to hold window data
	GLFWwindow* appWindow = glfwCreateWindow(1280, 720, "OpenGL Renderer", nullptr, nullptr);
	if (appWindow == nullptr)
	{
		std::puts("Failed to create a GLFW window.");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(appWindow);
	glfwSetFramebufferSizeCallback(appWindow, framebuffer_size_callback);

	// Initialize GLAD and load OpenGL function pointers
	if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == false)
	{
		std::puts("Failed to initialize GLAD.");
		return -1;
	}

	// Initialize OpenGL viewport (rendering space)
	glViewport(0, 0, 1280, 720);

	// Check for close window instruction; else, continue to render
	// Rendering Loop
	while (glfwWindowShouldClose(appWindow) == false)
	{
		// Check for user input
		ProcessUserInput(appWindow);

		// Render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Paint the viewport a color
		glClear(GL_COLOR_BUFFER_BIT); // Clear color buffer before the next frame

		// Swap buffers and poll for IO events
		glfwSwapBuffers(appWindow);
		glfwPollEvents();
	}

	// Clean up all resources and terminate application correctly
	glfwTerminate();
	return 0;
}

// Callback function to resize the viewport if the user resizes the window
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// Check for user input and react 
void ProcessUserInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}