#include "../include/Simulation.h"
#include "../Imgui/imgui.h"
#include "../Imgui/imgui_impl_glfw.h"
#include "../Imgui/imgui_impl_opengl3.h"
bogong::Simulation::Simulation()
{
	m_Shader.LoadShader("shaders/BasicVertexShader.glsl", bogong::ShaderType::VERTEX);
	m_Shader.LoadShader("shaders/BasicFragmentShader.glsl", bogong::ShaderType::FRAGMENT);
	m_Shader.LoadProgram();
	
	gerstener.LoadShader("shaders/GerstenerWaveVertex.glsl", bogong::ShaderType::VERTEX);
	gerstener.LoadShader("shaders/GerstenerWaveFragment.glsl", bogong::ShaderType::FRAGMENT);
	gerstener.LoadProgram();

	assert(!error());
	gwave = std::make_shared<cuda::GerstnerWave>(128,128);
	gwave->SetShader(gerstener);
	assert(!error());
	m_Shader.Bind();
	camera = std::make_shared<FPCamera>();
	assert(!error());	
}

void bogong::Simulation::Update(const std::shared_ptr<bogong::Keyboard> &kbd,const std::shared_ptr<bogong::Mouse> &mouse,
                                float delta)
{
	camera->Update(kbd, mouse, delta);
	m_Shader.Bind();
	assert(!error());
	m_Shader.setMat4("projection", camera->GetProjection());
	m_Shader.setMat4("view", camera->GetView());
	gerstener.Bind();
	gerstener.setMat4("projection", camera->GetProjection());
	gerstener.setMat4("view", camera->GetView());
	assert(!error());
	gwave->Update(delta);
}

void bogong::Simulation::Draw() const
{
	gwave->Draw();
	assert(!error());
}
