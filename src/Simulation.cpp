#include "../include/Simulation.h"

bogong::Simulation::Simulation()
{
	m_Shader.LoadShader("shaders/BasicVertexShader.glsl", bogong::ShaderType::VERTEX);
	m_Shader.LoadShader("shaders/BasicFragmentShader.glsl", bogong::ShaderType::FRAGMENT);
	m_Shader.LoadProgram();
	assert(!error());

	plane = std::make_shared<Plane>();
	plane->setShader(m_Shader);
	assert(!error());

	camera = std::make_shared<FPCamera>();
	assert(!error());
}

void bogong::Simulation::Update(std::shared_ptr<bogong::Keyboard> &kbd, std::shared_ptr<bogong::Mouse> &mouse,
                                float delta)
{
	m_Shader.Bind();
	camera->Update(kbd, mouse, delta);
	m_Shader.setMat4("projection", camera->GetProjection());
	assert(!error());
	m_Shader.setMat4("view", camera->GetView());
	assert(!error());
}

void bogong::Simulation::Draw() const
{
	assert(!error());

	plane->Draw();
	assert(!error());
}
