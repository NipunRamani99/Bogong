#include "../include/Simulation.h"
#include "../Imgui/imgui.h"
#include "../Imgui/imgui_impl_glfw.h"
#include "../Imgui/imgui_impl_opengl3.h"
bogong::Simulation::Simulation()
{
	m_Shader.LoadShader("shaders/BasicVertexShader.glsl", bogong::ShaderType::VERTEX);
	m_Shader.LoadShader("shaders/BasicFragmentShader.glsl", bogong::ShaderType::FRAGMENT);
	m_Shader.LoadProgram();
	origin_viz = std::make_shared<cuda::viz::OriginViz>();
	origin_viz->SetShader(m_Shader);
	heat_map = std::make_shared<cuda::viz::Heatmap>();
	heat_map->SetShader(m_Shader);
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
	
}

void bogong::Simulation::Draw() const
{
	origin_viz->Draw();
	heat_map->Draw();
	assert(!error());
}
