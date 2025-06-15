#pragma once
#include <iostream>
#include <vector>
#include <filesystem>
#include "../Common/QwertyTypes.h"

namespace Util {
	
	// File
	std::vector<FileInfo> IterateDirectory(const std::string& directory, std::vector<std::string> extensions);
	inline std::string GetFullPath(const std::filesystem::directory_entry& entry);
	inline std::string GetFileNameWithoutExtension(const std::filesystem::path& entry);
	inline std::string GetFileExtension(const std::filesystem::path& entry);
}