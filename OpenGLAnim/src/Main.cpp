#include <iostream>
#include "BackEnd/BackEnd.h"
#include "API/OpenGL/Renderer/GL_renderer.h"
#include "Core/Game.h"
#include "AssetManagement/AssetManager.h"

int main()
{
	std::cout << "starting new session!\n";

	if (!BackEnd::Init(API::OPENGL, WindowedMode::WINDOWED)) {
		std::cout << "BackEnd::Init() FAILED!\n";
		return -1;
	}

	while (BackEnd::WindowIsOpen())
	{
		BackEnd::UpdateSubSystems();
		BackEnd::BeginFrame();

		if (!AssetManager::LoadingComplete()) {
			AssetManager::UpdateLoading();
		}
		else {
			// before that loading assest: models, etc
			BackEnd::UpdateGame();
			OpenGLRenderer::RenderGame();
		}

		BackEnd::EndFrame();
	}
}