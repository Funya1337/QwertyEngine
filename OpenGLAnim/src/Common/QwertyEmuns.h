#pragma once
#include <cstdint>

enum class API {
	OPENGL,
	VULKAN,
	UNDEFINED
};

enum class WindowedMode {
	WINDOWED,
	FULLSCREEN
};

enum class SplitscreenMode {
	FULLSCREEN,
	TWO_PLAYER,
	FOUR_PLAYER,
	SPLITSCREEN_MODE_COUNT
};

enum class LoadingState {
	AWAITING_LOADING_FROM_DISK,
	LOADING_FROM_DISK,
	LOADING_COMPLETE
};

enum class ImageDataType {
	UNCOMPRESSED,
	COMPRESSED,
	EXR,
	UNDEFINED
};