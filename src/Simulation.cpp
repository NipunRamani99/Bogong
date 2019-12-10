#include "../include/Simulation.h"
#include "../Imgui/imgui.h"
#include "../Imgui/imgui_impl_glfw.h"
#include "../Imgui/imgui_impl_opengl3.h"
bogong::Simulation::Simulation()
{
	m_Shader.LoadShader("shaders/BasicVertexShader.glsl", bogong::ShaderType::VERTEX);
	m_Shader.LoadShader("shaders/BasicFragmentShader.glsl", bogong::ShaderType::FRAGMENT);
	m_Shader.LoadProgram();
	
	
	assert(!error());
	quad = std::make_shared<cuda::StableFluid::Quad>();
	quad->SetShader(m_Shader);
	assert(!error());
}

void bogong::Simulation::Update(const std::shared_ptr<bogong::Keyboard> &kbd,const std::shared_ptr<bogong::Mouse> &mouse,
                                float delta)
{
	
}

void bogong::Simulation::Draw() const
{
	quad->Draw();
	assert(!error());
}
