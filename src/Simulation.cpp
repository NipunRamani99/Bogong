#include "../include/Simulation.h"
#include "../Imgui/imgui.h"
#include "../Imgui/imgui_impl_glfw.h"
#include "../Imgui/imgui_impl_opengl3.h"
#include "../include/Defs.h"
bogong::Simulation::Simulation()
{
	m_Shader.LoadShader("shaders/BasicVertexShader.glsl", bogong::ShaderType::VERTEX);
	m_Shader.LoadShader("shaders/BasicFragmentShader.glsl", bogong::ShaderType::FRAGMENT);
	m_Shader.LoadProgram();
	quad_shader.LoadShader("shaders/QuadVertexShader.glsl",bogong::ShaderType::VERTEX);
	quad_shader.LoadShader("shaders/QuadFragmentShader.glsl",bogong::ShaderType::FRAGMENT);
	quad_shader.LoadProgram();

	assert(!error());
	quad = std::make_shared<cuda::Heat2D::Quad>();
	quad->SetShader(quad_shader);
	assert(!error());
	camera = std::make_shared<FPCamera>();
	assert(!error());
	
}

void bogong::Simulation::Update(const std::shared_ptr<bogong::Keyboard> &kbd,const std::shared_ptr<bogong::Mouse> &mouse,
                                float delta)
{
	camera->Update(kbd, mouse, delta);
	m_Shader.Bind();
	m_Shader.setMat4("projection", camera->GetProjection());
	m_Shader.setMat4("view", camera->GetView());
	camera->InputPos();
	quad->Update(delta);
}

void bogong::Simulation::Draw() const
{
	glViewport(0, 0, 1366, 768);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	quad->Draw();
	assert(!error());
}
