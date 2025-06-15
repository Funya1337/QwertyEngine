#pragma once
#include "../Common/QwertyEmuns.h"

namespace BackEnd {
	const API GetAPI();
	bool Init(API api, WindowedMode windowMode);

	void* GetWindowPointer();
	bool WindowIsOpen();
	void UpdateSubSystems();
	void BeginFrame();
	void EndFrame();
	void UpdateGame();
}