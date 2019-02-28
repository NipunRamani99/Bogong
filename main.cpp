#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "Init.hpp"
#include "Shaders.hpp"

#include <glm/glm.hpp>
#include <cuda_runtime.h>
#include <cuda_gl_interop.h>
static const GLfloat g_vertex_buffer_data[] = {
	-0.50f, 0.0f, 0.0f,
	-0.50f, 0.50f, 0.0f,
	 0.50f, 0.50f, 0.0f,
	 0.50f, 0.0f, 0.0f
};
static const GLfloat g_fragment_buffer_data[] =
{
	0.0f,0.0f,0.0f,
	1.0f,-1.0f,0.0f,
	0.0f,1.0f,0.0f,

};
GLuint VertexArrayID;
GLuint vertexbuff;

void CheckGLError();
void makeTriangle();

int main()
{
	int err = 0;
	cudaDeviceProp deviceProp;
	int gpuDevice = 0;
	int device_count = 0;
	cudaGetDeviceCount(&device_count);

	Init::InitGLFW();
	auto window = Init::CreateWindow(500, 500, "Mic Check.");
	Init::SetGLFWWindow(*window,4, 3, 3, GLFW_OPENGL_CORE_PROFILE,true);

	glewExperimental = true;

	if (glewInit() != GLEW_OK) {
		std::cout << "Couldn't init glew.";
		return 0;
	}
	if (err != 0)
	{
		return err;
	}
	cudaGLSetGLDevice(0);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	GLuint programID = LoadShaders("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");


	glGenVertexArrays(1, &VertexArrayID);

	glBindVertexArray(VertexArrayID);

	glGenBuffers(1, &vertexbuff);

	glBindBuffer(GL_ARRAY_BUFFER, vertexbuff);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	glEnableVertexArrayAttrib(VertexArrayID, 0);
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(float)*3,
		(void*)0
	);
	cudaGLRegisterBufferObject(vertexbuff);
	
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glUseProgram(programID);
	glPointSize(12);
	do {
		//Clear the screen. Can cause flickering if not done
		glClear(GL_COLOR_BUFFER_BIT);
		//Draw Nothing, not yet.
		//Swap Buffers
		makeTriangle();
		glfwSwapBuffers(window);
		glfwPollEvents();
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);


	return 0;
}

void makeTriangle()
{
	// Draw the tringle !

	glDrawArrays(GL_TRIANGLES, 0, 4); // Starting from vertex 0; 3 vertices total -> 1 triangle
}


void CheckGLError()
{
	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
	{
		std::string error;

		switch (err) {
		case GL_INVALID_OPERATION:      error = "INVALID_OPERATION";      break;
		case GL_INVALID_ENUM:           error = "INVALID_ENUM";           break;
		case GL_INVALID_VALUE:          error = "INVALID_VALUE";          break;
		case GL_OUT_OF_MEMORY:          error = "OUT_OF_MEMORY";          break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:  error = "INVALID_FRAMEBUFFER_OPERATION";  break;
		}

		Init::LogError(error);
		err = glGetError();
	}
}



