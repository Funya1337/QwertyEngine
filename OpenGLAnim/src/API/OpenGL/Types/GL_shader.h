#pragma once
#include <glm/glm.hpp>
#include <unordered_map>
#include <string>
#include <vector>

struct OpenGLShaderModule {
public:
	OpenGLShaderModule(const std::string& filename);
	bool CompilationFailed();
	int GetHandle();
	std::string& GetFilename();
	std::string& GetErrors();

private:
	int m_handle = -1;
	std::string m_filename = "";
	std::string m_errors = "";
};

struct OpenGLShader {
public:
	OpenGLShader() = default;
	OpenGLShader(std::vector<std::string> shaderPaths);
	bool Load(std::vector<std::string> shaderPaths);
	bool Hotload();
	void SetFloat(const std::string& name, float value);
	void SetInt(const std::string& name, int value);
	void Bind();

private:
	std::vector<std::string> m_shaderPaths;
	std::unordered_map<std::string, int> m_uniformLocations;
	int m_handle = -1;
};