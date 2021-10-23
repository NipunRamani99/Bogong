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
//	gerstener.LoadShader("shaders/GerstenerWaveTessControlShader.glsl", bogong::ShaderType::TESS_CONTROL);
//	gerstener.LoadShader("shaders/GerstenerWaveTessEvalShader.glsl", bogong::ShaderType::TESS_EVAL);
	gerstener.LoadProgram();
    
	// One vertex becomes one tessellated triangle.
   // glPatchParameteri(GL_PATCH_VERTICES,3);
	
	assert(!error());
	gwave = std::make_shared<cuda::GerstnerWave>(128, 128);
	gwave->SetShader(gerstener);
	plane = std::make_shared<Plane>();
	plane->setShader(m_Shader);
	assert(!error());
	m_Shader.Bind();
	camera = std::make_shared<FPCamera>();
	assert(!error());	
}

void bogong::Simulation::Update(const std::shared_ptr<bogong::Keyboard> &kbd,
								const std::shared_ptr<bogong::Mouse> &mouse, 
								GLFWwindow * glfwWindow, float delta)
{
	toggle(kbd, mouse, delta, glfwWindow);
	m_Shader.Bind();
	assert(!error());
	m_Shader.setMat4("projection", camera->GetProjection());
	m_Shader.setMat4("view", camera->GetView());
	gerstener.Bind();
	gerstener.setVec3("lightPos", lightPos);
	gerstener.setVec3("viewPos", camera->cameraPos);
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

 void bogong::Simulation::toggle(std::shared_ptr<Keyboard> kbd, std::shared_ptr<Mouse> mouse, float delta, GLFWwindow * window) {
	if (kbd->isKeyPressed(KEY::KEY_K))
	{
		if (canToggle) {
			isMouseEnabled = !isMouseEnabled;
			canToggle = false;
			if (!isMouseEnabled) {
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				glfwSetCursorPos(window, 640, 360);
				mouse->x = 640;
				mouse->y = 360;
				camera->ClearMouse(mouse);
				ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NoMouse;
			}
			else {
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

				ImGui::GetIO().ConfigFlags &= ~ImGuiConfigFlags_NoMouse;
			}
		}

	}
	if (!isMouseEnabled)
		camera->Update(kbd, mouse, delta);
	if (!canToggle) {
		timer += delta;
		if (timer >= 0.1f) {
			canToggle = true;
			timer = 0.0f;
		}
	}

}
