#include "GL_renderer.h"
#include "../GL_backEnd.h"
#include "../../../AssetManagement/AssetManager.h"
#include <iostream>
#include <unordered_map>

namespace OpenGLRenderer {
	std::unordered_map<std::string, OpenGLShader> g_shaders;
	GLuint g_diffuseTexture = 0;

	void LoadShaders();

	void Init()
	{
		std::cout << "Init OPENGL renderer\n";
		std::cout << "Loading shaders...\n";
		LoadShaders();
		//g_diffuseTexture = AssetManager::LoadTexture("res/textures/red-brick.png");
	}

	void LoadShaders()
	{
		g_shaders["Default"] = OpenGLShader({ "GL_default.vert", "GL_default.frag" });
	}

	OpenGLShader* GetShader(const std::string& name) {
		auto it = g_shaders.find(name);
		return (it != g_shaders.end()) ? &it->second : nullptr;
	}

	void RenderGame()
	{
		glDisable(GL_DITHER);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		
		OpenGLShader* shader = GetShader("Default");

		shader->Bind();
		shader->SetInt("textureSampler", 0);
		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, g_diffuseTexture);

		glBindVertexArray(OpenGLBackEnd::GetVertexDataVAO());
		glDrawElements(GL_TRIANGLES, OpenGLBackEnd::GetIndexCount(), GL_UNSIGNED_INT, (void*)0);
	}

	void HotloadShaders()
	{
		bool allSucceeded = true;
		for (auto& [_, shader] : g_shaders) {
			if (!shader.Hotload()) {
				allSucceeded = false;
			}
		}
		if (allSucceeded) {
			std::cout << "Hotloaded shaders\n";
		}
	}
}