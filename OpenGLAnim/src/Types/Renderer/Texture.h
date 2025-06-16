#pragma once
#include "../../Common/QwertyEnums.h"
#include "../../API/OpenGL/Types/Gl_texture.h"
#include <stb/stb_image.h>
#include <string>
#include <vector>
#include <iostream>

struct Texture {
public:
	Texture() = default;
	void Load();
	TextureData LoadUncompressedTextureData(const std::string& filePath);
	void SetLoadingState(LoadingState loadingState);
	void SetFileInfo(FileInfo fileInfo);
	void SetImageDataType(ImageDataType imageDataType);
	void SetTextureWrapMode(TextureWrapMode textureWrapMode);
	void SetMinFilter(TextureFilter textureMinFilter);
	void SetMagFilter(TextureFilter textureMagFilter);
	void PrintDebugInfo();
	void RequestMipmaps();

	const std::string& GetFileName();
	int GetMipmapLevelCount() const;
	bool MipmapsAreRequested() const;
	LoadingState GetLoadingState() const;
	OpenGLTexture& GetGLTexture();
	const TextureWrapMode GetTextureWrapMode();
	const TextureFilter GetMinFilter();
	const TextureFilter GetMagFilter();
	const ImageDataType GetImageDataType();
	const int GetFormat();
	const int GetChannelCount();
	const int GetInternalFormat();
	const int GetWidth(int mipmapLevel);
	const int GetHeight(int mipmapLevel);

	TextureData* GetTextureDataLevel0();

private:
	OpenGLTexture m_glTexture;
	LoadingState m_loadingState = LoadingState::AWAITING_LOADING_FROM_DISK;
	ImageDataType m_imageDataType = ImageDataType::UNDEFINED;
	TextureWrapMode m_wrapMode = TextureWrapMode::REPEAT;
	TextureFilter m_minFilter = TextureFilter::NEAREST;
	TextureFilter m_magFilter = TextureFilter::NEAREST;
	FileInfo m_fileInfo;
	std::vector<TextureData> m_textureDataLevels;
	
	int m_mipmapLevelCount = 0;
	bool m_mipmapsRequested = false;
};