#pragma once
#include "Init.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.h"
#include "Imgui.h"
#include "Callbacks.h"
#include "Simulation.h"
#include "Camera.h"
#include "Keyboard.h"
#include "Mouse.h"
#define WIDTH 800
#define HEIGHT 600
namespace bogong
{
	class Engine
	{
	private:
		GLFWwindow * window;
		GLuint programID;
		std::shared_ptr<IsometricCamera> camera;
		std::shared_ptr<Simulation> sim;
		Keyboard kbd;
		Mouse mouse;
		int camID = 0;
		double prevTime = 0.0;
		double currentTime = 0.0;
	public:

		bool KeepRendering = true;
		Engine()
		{
			int gpuDevice = 0;
			int device_count = 0;
			Init::InitGLFW();
			window = bogong::Init::CreateWindowGL(WIDTH, HEIGHT, "Mic Check.");
			Init::SetGLFWWindow(*window, 4, 3, 3, GLFW_OPENGL_CORE_PROFILE, true);
			glewExperimental = true;
			if (glewInit() != GLEW_OK) {
				std::cout << "Couldn't init glew.";
			}
			camera = std::make_shared<IsometricCamera>();
			kbd.SetCallback(window);
			mouse.SetCallback(window);
			Init::InitImgui(*window);
			//glEnable(GL_DEPTH_TEST);
			//glEnable(GL_BLEND);
			//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			//glEnable(GL_CULL_FACE);
			//glFrontFace(GL_CCW);

		}
		void Start()
		{
			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			/*Shader shader;
			shader.LoadShader("shaders/vertexShader.glsl", ShaderType::VERTEX);
			shader.LoadShader("shaders/fragmentShader.glsl", ShaderType::FRAGMENT);
			shader.LoadProgram();*/
			assert((bool)!error());
			error();
			sim = std::make_shared<Simulation>();
			int display_w, display_h;
			glfwMakeContextCurrent(window);
			glfwGetFramebufferSize(window, &display_w, &display_h);
			
			glViewport(0, 0, display_w, display_h);
			

		}
		void Update(double deltime)
		{
			std::string coords = "X: "+ std::to_string(mouse.x) + " Y: " + std::to_string(mouse.y);
			ImGui::LabelText(coords.c_str(),"Test: ");
			sim->Update(kbd, mouse, (float)deltime);
		}
		void DrawCalls()
		{
			sim->Draw();
		}
		void RenderEverything()
		{
			DrawCalls();
			Init::Render();
			Init::EndImguiFrame();
			glfwSwapBuffers(window);
			if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			{
				KeepRendering = false;
			}
		}
		void Loop()
		{
			prevTime = currentTime;
			double currentTime = glfwGetTime();
			kbd.Flush();
			mouse.Flush();
			glfwPollEvents();
			if (kbd.isKeyPressed(KEY_A))
			{
				std::cout << "KEY A Is Pressed.";
			}
			if (kbd.isKeyRepeating(KEY_A))
			{
				std::cout << "KEY A Is Repeating.";
			}
			if (kbd.isKeyReleased(KEY_A))
			{
				std::cout << "KEY A Is Released.";
			}
			if (mouse.isButtonPressed(BUTTON::LMB))
			{
				std::cout << "LMB PRESSED.";
			}
			if (mouse.isButtonReleased(BUTTON::LMB))
			{
				std::cout << "LMB RELEASED.";
				std::cout << "X: " << mouse.x << " Y: " << mouse.y<<". " ;
			}
			Init::StartImguiFrame();
			Init::PrepareImguiFrame();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glfwPollEvents();
			Update(currentTime-prevTime);
			RenderEverything();
		}
		void End()
		{
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext();
			glfwDestroyWindow(window);
			glfwTerminate();
		}
	};
}