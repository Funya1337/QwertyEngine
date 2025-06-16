#include "AssetManager.h"

namespace AssetManager {

	std::vector<Mesh> g_meshes;
	std::vector<Model> g_models;
	std::vector<Texture> g_textures;

	std::vector<Vertex> g_vertices;
	std::vector<uint32_t> g_indices;
	
	bool g_loadingComplete = false;

	bool LoadingComplete() { return g_loadingComplete; }
	void FindAssetPaths();

	void Init()
	{
		FindAssetPaths();
		LoadPendingTexturesSync();
	}

	void UpdateLoading()
	{
		g_loadingComplete = true;

		for (Model& model : g_models)
		{
			if (model.GetLoadingState() != LoadingState::LOADING_COMPLETE)
			{
				g_loadingComplete = false;
				return;
			}
		}

		if (LoadingComplete())
		{
			BuildPrimitives();

			if (BackEnd::GetAPI() == API::OPENGL) {
				OpenGLBackEnd::UploadVertexData(g_vertices, g_indices);
			}
		}
	}

	void FindAssetPaths()
	{
		// File all textures
		for (FileInfo& fileInfo : Util::IterateDirectory("res/textures/uncompressed", { "png", "jpg" })) {
			Texture& texture = g_textures.emplace_back();
			texture.SetFileInfo(fileInfo);
			texture.SetImageDataType(ImageDataType::UNCOMPRESSED);
			texture.SetTextureWrapMode(TextureWrapMode::CLAMP_TO_BORDER);
			texture.SetMinFilter(TextureFilter::LINEAR_MIPMAP);
			texture.SetMagFilter(TextureFilter::LINEAR);
			texture.RequestMipmaps();
			//printf("------------------\n");

			//std::cout << "FileInfo\n";
			//std::cout << "Dir: " << fileInfo.dir << "\n";
			//std::cout << "Ext: " << fileInfo.ext << "\n";
			//std::cout << "Name: " << fileInfo.name << "\n";
			//std::cout << "Path: " << fileInfo.path << "\n";

			//printf("------------------\n");
		}
		//printf("find asset paths function\n");
	}

	std::vector<Mesh>& GetMeshes() {
		return g_meshes;
	}

	std::vector<Vertex>& GetVertices() {
		return g_vertices;
	}

	std::vector<uint32_t>& GetIndices() {
		return g_indices;
	}
	
	std::vector<Model>& GetModels() {
		return g_models;
	}

	std::vector<Texture>& GetTextures() {
		return g_textures;
	}
}