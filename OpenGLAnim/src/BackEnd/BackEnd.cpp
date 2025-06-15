#include "BackEnd.h"
#include "../Config/Config.h"
#include "../API/OpenGL/GL_backEnd.h"
#include "../API/OpenGL/Renderer/GL_renderer.h"
#include "../AssetManagement/AssetManager.h"
#include "../Input/Input.h"
#include "GLFWIntegration.h"
#include <iostream>

namespace BackEnd {

	API g_api = API::UNDEFINED;
	int g_presentTargetWidth = 0;
	int g_presentTargetHeight = 0;

	void UpdateLazyKeypresses();

	bool Init(API api, WindowedMode windowMode)
	{
		g_api = api;
		if (g_api == API::OPENGL) std::cout << "OPENGL\n";
		
		Config::Init();
		if (!GLFWIntegration::Init(api, windowMode)) {
			return false;
		}
		if (GetAPI() == API::OPENGL) {
			OpenGLBackEnd::Init();
			OpenGLRenderer::Init();
		}
		else if (GetAPI() == API::VULKAN) {
			std::cout << "init vulkan API\n";
			//if (!VulkanBackEnd::Init()) {
			//	return false;
			//}
		}
		AssetManager::Init();
		//UIBackEnd::Init();
		//Audio::Init();
		Input::Init(BackEnd::GetWindowPointer());
		//InputMulti::Init();
		//Gizmo::Init();
		//ViewportManager::Init();
		//Editor::Init();
		//EditorImGui::Init();
		//Synth::Init();
		//MidiFileManager::Init();
		//WeaponManager::Init();
		//Physics::Init();
		//ImGuiBackEnd::Init();

		//Modelling::Init();

		glfwShowWindow(static_cast<GLFWwindow*>(BackEnd::GetWindowPointer()));

		return true;
	}

	void UpdateSubSystems() {
		//float deltaTime = Game::GetDeltaTime();
		////glfwSwapInterval(0);

		//InputMulti::Update();
		//Synth::Update(deltaTime);
		//Audio::Update(deltaTime);
		//MidiFileManager::Update(deltaTime);
		Input::Update();

		UpdateLazyKeypresses();
	}

	void UpdateGame() {
		//if (Input::KeyPressed(QWERTY_KEY_0))
		//{
		//	std::cout << "asdfasdfasdf\n";
		//}
		const Resolutions& resolutions = Config::GetResolutions();
	}

	void BeginFrame() {
		GLFWIntegration::BeginFrame(g_api);
	}

	void EndFrame() {
		GLFWIntegration::EndFrame(g_api);
	}
	
	const API GetAPI() {
		return g_api;
	}

	void* GetWindowPointer() {
		return GLFWIntegration::GetWindowPointer();;
	}

	bool BackEnd::WindowIsOpen() {
		return GLFWIntegration::WindowIsOpen();
	}

	void UpdateLazyKeypresses() {
		if (Input::KeyPressed(QWERTY_KEY_H)) {
			OpenGLRenderer::HotloadShaders();
		}
	}
}