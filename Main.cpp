#include "Framework.h"
#include "Shaders.h"

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

	// Build and compile vertex shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	// Check for vertex shader compilation errors
	int successful;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &successful);
	if (!successful)
	{
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::cout << "VERTEX_SHADER_COMPILATION_FAILED.\n" << infoLog << std::endl;
	}

	// Build and compile fragment shader (OpenGL pixel shader)
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);

	// Check for fragment shader compilation errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &successful);
	if (!successful)
	{
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cout << "FRAGMENT_SHADER_COMPILATION_FAILED.\n" << infoLog << std::endl;
	}

	// Link the shaders
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// Check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &successful);
	if (!successful)
	{
		glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
		std::cout << "SHADER_PROGRAM_LINKING_FAILED.\n" << infoLog << std::endl;
	}

	// Clean up shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Define vertex data, buffers, and attributes
	float triangleVertices[] =
	{
		// Triangle vertices in NDC space
		-0.5f, -0.5f, 0.0f, 
		0.5f, -0.5f, 0.0f, 
		0.0f, 0.5f, 0.0f 
	};

	// Create a vertex array object
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create a vertex buffer object for triangle
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);

	// Set vertex attribute pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Check for close window instruction; else, continue to render
	// Rendering Loop
	while (glfwWindowShouldClose(appWindow) == false)
	{
		// Check for user input
		ProcessUserInput(appWindow);

		// Render background
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Paint the viewport a color (RGBA)
		glClear(GL_COLOR_BUFFER_BIT); // Clear color buffer before the next frame

		// Draw triangle
		glUseProgram(shaderProgram);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Swap buffers and poll for IO events
		glfwSwapBuffers(appWindow);
		glfwPollEvents();
	}

	// Clean up all resources and terminate application correctly
	glDeleteBuffers(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteProgram(shaderProgram);
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