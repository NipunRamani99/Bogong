#include "../include/Camera.h"
#include "../include/Keyboard.h"
#include "../Imgui/imgui.h"

namespace bogong {
	class Mouse;
}

glm::mat4 bogong::Camera::GetProjection()
{
	return projection;
}

glm::mat4 bogong::Camera::GetView()
{
	return view;
}

bogong::FPCamera::FPCamera()
{
	projection = glm::perspective(glm::radians(45.0f), float(screenWidth) / float(screenHeight), 0.1f, 100.0f);
	view = lookAt(cameraPos, cameraPos + cameraFront, up);
}

void bogong::FPCamera::Update(std::shared_ptr<Keyboard> kbd, std::shared_ptr<Mouse> mouse, float delta)
{
	float camSpeed = cameraSpeed * delta;
	if (kbd->isKeyPressed(KEY_W))
	{
		cameraPos += camSpeed * cameraFront;
	}
	if (kbd->isKeyPressed(KEY_S))
	{
		cameraPos -= camSpeed * cameraFront;
	}
	if (kbd->isKeyPressed(KEY_A))
	{
		cameraPos -= normalize(cross(cameraFront, up)) * camSpeed;
	}
	if (kbd->isKeyPressed(KEY_D))
	{
		cameraPos += normalize(cross(cameraFront, up)) * camSpeed;
	}
	view = lookAt(cameraPos, cameraPos + cameraFront, up);
	ImGui::DragFloat3("Position", reinterpret_cast<float*>(&cameraPos), 0.01, -1000, 1000);
}
