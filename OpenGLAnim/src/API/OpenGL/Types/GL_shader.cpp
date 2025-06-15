#include "GL_shader.h"
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

void ParseFile(const std::string& filepath, std::string& outputString, std::vector<std::string>& lineToFile, std::vector<std::string>& includedPaths);
int GetErrorLineNumber(const std::string& error);
std::string GetErrorMessage(const std::string& line);
std::string GetLinkingErrors(unsigned int shader);
std::string GetShaderCompileErrors(unsigned int shader, const std::string& filename, const std::vector<std::string>& lineToFile);
std::string StripBOM(const std::string& source);

OpenGLShader::OpenGLShader(std::vector<std::string> shaderPaths)
{
	m_shaderPaths = shaderPaths;
	Load(m_shaderPaths);
}

void OpenGLShader::Bind() {
	glUseProgram(m_handle);
}

bool OpenGLShader::Load(std::vector<std::string> shaderPaths)
{
	// Compile shader modules
	std::vector<OpenGLShaderModule> modules;
	for (std::string& shaderPath : shaderPaths) {
		modules.push_back(shaderPath);
	}

	// Print compilation errors
	bool errorsFound = false;
	for (OpenGLShaderModule& module : modules) {
		if (module.CompilationFailed()) {
			errorsFound = true;
			break;
		}
	}

	if (errorsFound)
	{
		std::cout << "\n-------------------------------------------------------------------------\n\n";
		for (OpenGLShaderModule& module : modules) {
			if (module.CompilationFailed()) {
				std::cout << " COMPILATION ERROR: " << module.GetFilename() << "\n\n";
				std::cout << module.GetErrors() << "\n";
			}
			glDeleteShader(module.GetHandle());
		}
		std::cout << "-------------------------------------------------------------------------\n";
		return false;
	}

	// Attempt to link
	int tempHandle = glCreateProgram();
	for (OpenGLShaderModule& module : modules) {
		glAttachShader(tempHandle, module.GetHandle());
	}
	glLinkProgram(tempHandle);
	std::string linkingErrors = GetLinkingErrors(tempHandle);

	if (linkingErrors.length())
	{
		std::cout << "\n-------------------------------------------------------------------------\n\n";
		std::cout << " LINKING ERROR: ";
		for (int i = 0; i < modules.size(); i++) {
			std::cout << modules[i].GetFilename();
			if (i != modules.size() - 1) {
				std::cout << "/";
			}
		}
		std::cout << linkingErrors << "\n";
		std::cout << "-------------------------------------------------------------------------\n";
		for (OpenGLShaderModule& module : modules) {
			glDeleteShader(module.GetHandle());
		}
		return false;
	}
	else
	{
		if (m_handle != -1) {
			glDeleteProgram(m_handle);
		}
		m_handle = tempHandle;
		m_uniformLocations.clear();
	}
	for (OpenGLShaderModule& module : modules) {
		glDeleteShader(module.GetHandle());
	}
	return true;
}

bool OpenGLShader::Hotload() {
	return Load(m_shaderPaths);
}

void OpenGLShader::SetFloat(const std::string& name, float value) {
	if (m_uniformLocations.find(name) == m_uniformLocations.end()) {
		m_uniformLocations[name] = glGetUniformLocation(m_handle, name.c_str());
	}
	glUniform1f(m_uniformLocations[name], value);
}

void OpenGLShader::SetInt(const std::string& name, int value) {
	if (m_uniformLocations.find(name) == m_uniformLocations.end()) {
		m_uniformLocations[name] = glGetUniformLocation(m_handle, name.c_str());
	}
	glUniform1i(m_uniformLocations[name], value);
}

int OpenGLShaderModule::GetHandle() {
	return m_handle;
}

std::string& OpenGLShaderModule::GetFilename() {
	return m_filename;
}

std::string& OpenGLShaderModule::GetErrors() {
	return m_errors;
}

OpenGLShaderModule::OpenGLShaderModule(const std::string& filename)
{
	std::vector<std::string> lineMap;
	std::vector<std::string> includedPaths;
	std::string parsedShaderSource = "";
	ParseFile("res/shaders/OpenGL/" + filename, parsedShaderSource, lineMap, includedPaths);
	parsedShaderSource = StripBOM(parsedShaderSource);

	std::string extension = std::filesystem::path(filename).extension().string();
	static const std::unordered_map<std::string, int> shaderTypeMap = {
		{".vert", GL_VERTEX_SHADER},
		{".frag", GL_FRAGMENT_SHADER},
		{".geom", GL_GEOMETRY_SHADER},
		{".tesc", GL_TESS_CONTROL_SHADER},
		{".tese", GL_TESS_EVALUATION_SHADER},
		{".comp", GL_COMPUTE_SHADER}
	};
	int shaderType = shaderTypeMap.contains(extension) ? shaderTypeMap.at(extension) : GL_NONE;

	const char* shaderCode = parsedShaderSource.c_str();
	m_handle = glCreateShader(shaderType);
	glShaderSource(m_handle, 1, &shaderCode, NULL);
	glCompileShader(m_handle);
	m_errors = GetShaderCompileErrors(m_handle, filename, lineMap);
	m_filename = filename;
}

bool OpenGLShaderModule::CompilationFailed() {
	return m_errors.length();
}

void ParseFile(const std::string& filepath, std::string& outputString, std::vector<std::string>& lineToFile, std::vector<std::string>& includedPaths)
{
	std::string baseDir = std::filesystem::path(filepath).parent_path().string();
	std::string filename = std::filesystem::path(filepath).filename().string();
	std::ifstream file(filepath);
	std::string line;
	int lineNumber = 0;
	bool versionInserted = false;

	while (std::getline(file, line))
	{
		if (line.find("#include") != std::string::npos) {
			size_t start = line.find("\"") + 1;
			size_t end = line.find("\"", start);
			std::string includeFile = line.substr(start, end - start);
			std::string includePath = std::filesystem::weakly_canonical(baseDir + "/" + includeFile).string();
			if (std::find(includedPaths.begin(), includedPaths.end(), includePath) == includedPaths.end()) {
				includedPaths.push_back(includePath);
				ParseFile(includePath, outputString, lineToFile, includedPaths);
			}
		}
		else
		{
			outputString += line + "\n";
			lineToFile.emplace_back(filename + " (line " + std::to_string(lineNumber++) + ")");
		}
	}
}

std::string GetShaderCompileErrors(unsigned int shader, const std::string& filename, const std::vector<std::string>& lineToFile) {
	int success;
	char infoLog[1024];
	std::string result = "";
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
		// Parse error log to extract line numbers
		std::stringstream logStream(infoLog);
		std::string line;
		while (std::getline(logStream, line)) {  
			if ((line.substr(0, 7) == "ERROR: ")) {
				int lineNumber = GetErrorLineNumber(line);
				if (lineNumber >= 0 && lineNumber < lineToFile.size()) {
					result += "  " + lineToFile[lineNumber] + ": " + GetErrorMessage(line) + "\n";
				}
			}
		}
	}
	return result;
}

std::string GetLinkingErrors(unsigned int programId) {
	GLint linkStatus;
	glGetProgramiv(programId, GL_LINK_STATUS, &linkStatus);

	if (linkStatus == GL_FALSE) {
		GLint logLength;
		glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logLength);

		if (logLength > 0) {
			std::vector<char> infoLogBuffer(logLength + 1); // +1 for null terminator
			glGetProgramInfoLog(programId, logLength, NULL, &infoLogBuffer[0]);

			std::string fullLog(infoLogBuffer.data());
			std::stringstream logStream(fullLog);
			std::string line;
			std::string resultToShow = "\n";

			const std::string assemblyStartDelimiter = "-- internal assembly text --";
			bool assemblySectionEncountered = false;

			while (std::getline(logStream, line)) {
				if (assemblySectionEncountered) {
					break;
				}

				resultToShow += "    " + line + "\n";

				// Now, check if THIS line was the delimiter
				if (line.find(assemblyStartDelimiter) != std::string::npos) {
					resultToShow += "    (Following internal assembly text omitted for brevity)\n";
					assemblySectionEncountered = true;
					break;
				}
			}
			return resultToShow;
		}
		else {
			return "\n    An unknown linking error occurred (no info log available).\n";
		}
	}
	return "";
}

std::string GetErrorMessage(const std::string& line) {
	size_t firstColon = line.find(':');
	if (firstColon != std::string::npos) {
		size_t secondColon = line.find(':', firstColon + 1);
		if (secondColon != std::string::npos) {
			size_t thirdColon = line.find(':', secondColon + 1);
			if (thirdColon != std::string::npos) {
				size_t messageStart = thirdColon + 2; // Skip the colon and space
				if (messageStart < line.length()) {
					return line.substr(messageStart);
				}
			}
		}
	}
	return ""; // Return empty string if parsing fails
}

int GetErrorLineNumber(const std::string& error) {
	size_t firstColon = error.find(':');
	if (firstColon != std::string::npos) {
		size_t secondColon = error.find(':', firstColon + 1);
		if (secondColon != std::string::npos) {
			size_t thirdColon = error.find(':', secondColon + 1);
			if (thirdColon != std::string::npos) {
				std::string lineNumberStr = error.substr(secondColon + 1, thirdColon - secondColon - 1);
				return std::stoi(lineNumberStr);
			}
		}
	}
	return -1;
}

std::string StripBOM(const std::string& source)
{
	const std::string bom = "\xEF\xBB\xBF";
	if (source.compare(0, bom.size(), bom) == 0)
		return source.substr(bom.size());
	return source;
}