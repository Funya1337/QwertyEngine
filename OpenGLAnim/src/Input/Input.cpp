#include "Input.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace Input {
	
	bool g_keyPressed[372];
	bool g_keyDown[372];
	bool g_keyDownLastFrame[372];
	GLFWwindow* g_window;

	void Init(void* glfwWindow)
	{
		g_window = static_cast<GLFWwindow*>(glfwWindow);
	}

	void Update()
	{
		for (int i = 32; i < 349; ++i)
		{
			if (glfwGetKey(g_window, i) == GLFW_PRESS)
				g_keyDown[i] = true;
			else
				g_keyDown[i] = false;

			if (g_keyDown[i] && !g_keyDownLastFrame[i])
				g_keyPressed[i] = true;
			else
				g_keyPressed[i] = false;
			g_keyDownLastFrame[i] = g_keyDown[i];
		}
	}

	bool KeyPressed(unsigned int keycode) {
		return g_keyPressed[keycode];
	}
}