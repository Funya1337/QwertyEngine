#pragma once
#include "../../Common/QwertyEmuns.h"
#include "../../Common/QwertyTypes.h"
#include <string>
#include <vector>

struct Model {
	Model() = default;

	void SetLoadingState(LoadingState loadingState);
	void SetName(std::string modelName);
	void AddMeshIndex(uint32_t index);

	const LoadingState& GetLoadingState() const { return m_loadingState; }
	const size_t GetMeshCount()  const { return m_meshIndices.size(); }
	const std::string GetName() const { return m_name; }
	const std::vector<uint32_t>& GetMeshIndices() const { return m_meshIndices; }

	bool m_awaitingLoadingFromDisk = true;
	std::string m_fullPath = "";

private:
	std::string m_name = "undefined";
	std::vector<uint32_t> m_meshIndices;
	LoadingState m_loadingState = LoadingState::AWAITING_LOADING_FROM_DISK;
};