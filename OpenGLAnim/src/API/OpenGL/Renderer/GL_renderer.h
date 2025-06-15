#pragma once
#include "../Types/GL_shader.h"

namespace OpenGLRenderer {
	void Init();
	void RenderGame();
	void HotloadShaders();
	OpenGLShader* GetShader(const std::string& name);
}