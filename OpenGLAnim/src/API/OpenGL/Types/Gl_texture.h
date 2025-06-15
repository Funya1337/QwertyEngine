#pragma once
#include "../../../Common/QwertyTypes.h"
#include "../../../Common/QwertyEmuns.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

struct OpenGLTexture {
public:
	OpenGLTexture() = default;
	void AllocateMemory(int width, int height, int format, int internalFormat, int mipmapLevelCount);
	GLuint& GetHandle();

private:
	GLuint m_handle = 0;
	bool m_memoryAllocated = false;
	int m_width = 0;
	int m_height = 0;
	GLint m_mipmapLevelCount = 0;
	ImageDataType m_imageDataType;
};