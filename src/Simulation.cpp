#include "../include/Simulation.h"
#include "../Imgui/imgui.h"
#include "../Imgui/imgui_impl_glfw.h"
#include "../Imgui/imgui_impl_opengl3.h"
bogong::Simulation::Simulation()
{
	m_Shader.LoadShader("shaders/BasicVertexShader.glsl", bogong::ShaderType::VERTEX);
	m_Shader.LoadShader("shaders/BasicFragmentShader.glsl", bogong::ShaderType::FRAGMENT);
	m_Shader.LoadProgram();
	quad_shader.LoadShader("shaders/QuadVertexShader.glsl",bogong::ShaderType::VERTEX);
	quad_shader.LoadShader("shaders/QuadFragmentShader.glsl",bogong::ShaderType::FRAGMENT);
	quad_shader.LoadProgram();

	assert(!error());
	fb_test = std::make_shared<FrameBufferTest>();
	assert(!error());
	frame_quad = std::make_shared<FrameBufferQuad>();
	frame_quad->SetShader(quad_shader);
	origin_viz = std::make_shared<cuda::viz::OriginViz>();
	origin_viz->SetShader(m_Shader);
	heat_map = std::make_shared<cuda::viz::Heatmap>();
	heat_map->SetShader(m_Shader);
	frame_quad->AddTexture(fb_test->get_texture());
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
	glEnable(GL_DEPTH_TEST);
	fb_test->BindFBO();
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	origin_viz->Draw();
	heat_map->Draw();
	fb_test->UnbindFBO();
	glDisable(GL_DEPTH_TEST);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	frame_quad->Draw();
	assert(!error());
}
