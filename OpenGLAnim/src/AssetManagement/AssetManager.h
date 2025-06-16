#pragma once
#include "../Types/Renderer/Mesh.h"
#include "../Types/Renderer/Model.h"
#include "../Types/Renderer/Texture.h"
#include "../Common/QwertyTypes.h"
#include "../API/OpenGL/GL_backEnd.h"
#include "../BackEnd/BackEnd.h"
#include "../Utils/Util.h"
#include <vector>
#include <iostream>
#include <filesystem>

namespace AssetManager {
	void Init();
	void UpdateLoading();
	bool LoadingComplete();

	// Mesh
	std::vector<Mesh>& GetMeshes();
	int CreateMesh(const std::string& name, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices, glm::vec3 aabbMin, glm::vec3 aabbMax, int parentIndex, glm::mat4 localTransform, glm::mat4 inverseBindTransform);
	int CreateMesh(const std::string& name, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);

	// Vertex data
	std::vector<Vertex>& GetVertices();
	std::vector<uint32_t>& GetIndices();

	// Models
	std::vector<Model>& GetModels();
	Model* CreateModel(const std::string& name);

	// Textures
	std::vector<Texture>& GetTextures();
	void LoadPendingTexturesSync();
	void LoadTexture(Texture* texture);
	Texture* GetTextureByIndex(int index);

	// Building
	void BuildPrimitives();
}