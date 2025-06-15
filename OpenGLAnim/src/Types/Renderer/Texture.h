#pragma once
#include "../../Common/QwertyEnums.h"
#include "../../API/OpenGL/Types/Gl_texture.h"
#include <string>
#include <iostream>

struct Texture {
public:
	Texture() = default;
	void Load();
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

private:
	OpenGLTexture m_glTexture;
	LoadingState m_loadingState = LoadingState::AWAITING_LOADING_FROM_DISK;
	ImageDataType m_imageDataType = ImageDataType::UNDEFINED;
	TextureWrapMode m_wrapMode = TextureWrapMode::REPEAT;
	TextureFilter m_minFilter = TextureFilter::NEAREST;
	TextureFilter m_magFilter = TextureFilter::NEAREST;
	FileInfo m_fileInfo;
	
	int m_mipmapLevelCount = 0;
	bool m_mipmapsRequested = false;
};