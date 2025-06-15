#pragma once
#include "../../Common/QwertyTypes.h"
#include "GL_backEnd.h"
#include "../../BackEnd/GLFWIntegration.h"
#include <string>
#include <iostream>
#include <vector>

namespace OpenGLBackEnd {

	GLuint g_vertexDataVAO = 0;
	GLuint g_vertexDataVBO = 0;
	GLuint g_vertexDataEBO = 0;
	static GLuint g_indexCount = 0;

	void APIENTRY glDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei /*length*/, const char* message, const void* /*userParam*/);

	void Init() {
		GLFWIntegration::MakeContextCurrent();
		glfwSwapInterval(true);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "Failed to initialize GLAD\n";
			return;
		}
		
		GLint major, minor;
		glGetIntegerv(GL_MAJOR_VERSION, &major);
		glGetIntegerv(GL_MINOR_VERSION, &minor);
		const GLubyte* vendor = glGetString(GL_VENDOR);
		const GLubyte* renderer = glGetString(GL_RENDERER);
		std::cout << "\nGPU: " << renderer << "\n";
		std::cout << "GL version: " << major << "." << minor << "\n\n";


		// For displaying errors
		int flags;
		glGetIntegerv(GL_CONTEXT_FLAGS, &flags);

		if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); // makes sure errors are displayed synchronously
			glDebugMessageCallback(glDebugOutput, nullptr);
		}
		else {
			std::cout << "Debug GL context not available\n";
		}

		glClear(GL_COLOR_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
	}

	void UploadVertexData(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
	{
		g_indexCount = static_cast<GLuint>(indices.size());
		glGenVertexArrays(1, &g_vertexDataVAO);
		glGenBuffers(1, &g_vertexDataVBO);
		glGenBuffers(1, &g_vertexDataEBO);

		glBindVertexArray(g_vertexDataVAO);
		glBindBuffer(GL_ARRAY_BUFFER, g_vertexDataVBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_vertexDataEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), &indices[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	GLuint GetIndexCount() {
		return g_indexCount;
	}

	void APIENTRY glDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei /*length*/, const char* message, const void* /*userParam*/)
	{
		if (id == 131169 || // Framebuffer detailed info: The driver allocated storage for renderbuffer [X].
			id == 131185 || // Buffer detailed info: The driver is using video memory for buffer [X].
			id == 131218 || // Program/shader state performance warning: Fragment shader in program [X] is being recompiled based on state.
			id == 131204 || // Texture state usage warning: Texture [X] is base level inconsistent. Level [0] has inconsistent dimensions or formats.
			id == 131154    // Pixel-path performance warning: Pixel transfer is synchronized with 3D rendering.
			) {
			return;
		}
		std::cout << "---------------\n";
		std::cout << "Debug message (" << id << "): " << message << "\n";
		switch (source) {
		case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
		case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
		case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
		case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
		case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
		}
		std::cout << "\n";
		switch (type) {
		case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
		case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
		case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
		case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
		case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
		case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
		case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
		}
		std::cout << "\n";
		switch (severity) {
		case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
		case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
		case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
		case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
		}    std::cout << "\n\n\n";
	}

	GLuint GetVertexDataVAO() { return g_vertexDataVAO; }
	GLuint GetVertexDataVBO() { return g_vertexDataVBO; }
	GLuint GetVertexDataEBO() { return g_vertexDataEBO; }
}