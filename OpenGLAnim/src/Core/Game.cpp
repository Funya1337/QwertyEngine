#include "Game.h"

namespace Game {

	SplitscreenMode g_splitscreenMode = SplitscreenMode::FULLSCREEN;

	void Create()
	{
		SetSplitscreenMode(SplitscreenMode::FULLSCREEN);
	}

	void SetSplitscreenMode(SplitscreenMode mode) {
		g_splitscreenMode = mode;
		//ViewportManager::UpdateViewports();
	}
}