#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../../Common/QwertyTypes.h"

#include <vector>

namespace OpenGLBackEnd {
	// Core
	void Init();

	// Buffers
	void UploadVertexData(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);

	GLuint GetVertexDataVAO();
	GLuint GetVertexDataVBO();
	GLuint GetVertexDataEBO();
	GLuint GetIndexCount();
}