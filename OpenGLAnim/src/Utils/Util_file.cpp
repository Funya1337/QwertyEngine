#include "Util.h"
#include <filesystem>

namespace Util {

	inline std::string GetFullPath(const std::filesystem::directory_entry& entry)
	{
		return entry.path().string();
	}

	inline std::string GetFileNameWithoutExtension(const std::filesystem::path& entry)
	{
		return entry.stem().string();
	}

	inline std::string GetFileExtension(const std::filesystem::path& entry)
	{
		return (entry.has_extension()) ? (entry.extension().string().substr(1)) : "";
	}

	std::vector<FileInfo> IterateDirectory(const std::string& directory, std::vector<std::string> extensions) {

		std::vector<FileInfo> fileInfoList;

		if (!std::filesystem::is_directory(directory)) return fileInfoList;

		for (const auto& entry : std::filesystem::directory_iterator(directory)) {
			if (!std::filesystem::is_regular_file(entry)) continue;

			FileInfo fileInfo = { GetFullPath(entry), GetFileNameWithoutExtension(entry), GetFileExtension(entry), directory };

			if (extensions.empty() || std::find(extensions.begin(), extensions.end(), fileInfo.ext) != extensions.end()) {
				fileInfoList.push_back(fileInfo);
			}
		}
		return fileInfoList;
	}
}