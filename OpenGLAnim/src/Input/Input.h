#pragma once
#include "keycodes.h"

namespace Input {
	void Init(void* glfwWinodw);
	void Update();
	bool KeyPressed(unsigned int keycode);
}