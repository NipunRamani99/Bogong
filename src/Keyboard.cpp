#include "../include/Keyboard.h"
namespace bogong {
	std::map<int, STATUS> Keyboard::KeyMap = std::map<int, STATUS>();

	Keyboard::Keyboard()
	{
		//Initialize the Container and set every isPressed value to false.
		for (int i = 0; i < 36; i++)
		{
			KeyMap.insert({i, NONE});
		}
	}

	void Keyboard::Flush()
	{
		for (auto& Key : Keyboard::KeyMap)
		{
			Key.second = NONE;
		}
	}

	void Keyboard::SetCallback(GLFWwindow* p_Window)
	{
		glfwSetKeyCallback(p_Window, Keyboard::Callback);
	}

	void Keyboard::Callback(GLFWwindow* p_Window, int p_Key, int p_Scancode, int p_Action, int mods)
	{
		if (p_Key >= 65 && p_Key <= 90)
		{
			p_Key = p_Key - 65;
			STATUS stat;
			if (p_Action == GLFW_PRESS)
				stat = IS_PRESSED;
			if (p_Action == GLFW_RELEASE)
				stat = IS_RELEASED;
			if (p_Action == GLFW_REPEAT)
				stat = IS_REPEATING;

			Keyboard::KeyMap.find(p_Key)->second = stat;
		}
	}

	bool Keyboard::isKeyPressed(KEY p_Key)
	{
		bool RetnVal = false;
		if (Keyboard::KeyMap.at(p_Key) == IS_PRESSED)
			RetnVal = true;
		return RetnVal;
	}

	bool Keyboard::isKeyRepeating(KEY p_Key)
	{
		bool RetnVal = false;
		if (Keyboard::KeyMap.at(p_Key) == IS_REPEATING)
			RetnVal = true;
		return RetnVal;
	}

	bool Keyboard::isKeyReleased(KEY p_Key)
	{
		bool RetnVal = false;
		if (Keyboard::KeyMap.at(p_Key) == IS_RELEASED)
			RetnVal = true;
		return RetnVal;
	}
}
