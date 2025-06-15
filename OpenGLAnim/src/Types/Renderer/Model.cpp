#include "Model.h"
#include "../../AssetManagement/AssetManager.h"
#include <stack>

void Model::SetLoadingState(LoadingState loadingState) {
    m_loadingState = loadingState;
}

void Model::AddMeshIndex(uint32_t index) {
    m_meshIndices.push_back(index);
}

void Model::SetName(std::string modelName) {
    m_name = modelName;
}