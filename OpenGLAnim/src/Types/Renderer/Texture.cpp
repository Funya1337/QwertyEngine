#include "Texture.h"

void Texture::Load()
{
    if (m_imageDataType == ImageDataType::UNCOMPRESSED) {
        std::cout << GetFileName() << std::endl;
        std::cout << "Uncompressed loading\n";
    }
    else if (m_imageDataType == ImageDataType::COMPRESSED) {
        std::cout << "Uncompressed loading\n";
    }
    else if (m_imageDataType == ImageDataType::EXR) {
        std::cout << "exr loading\n";
    }

    m_loadingState = LoadingState::LOADING_COMPLETE;
}

void Texture::SetFileInfo(FileInfo fileInfo) {
    m_fileInfo = fileInfo;
}

void Texture::SetImageDataType(ImageDataType imageDataType)
{
    m_imageDataType = imageDataType;
}

void Texture::SetTextureWrapMode(TextureWrapMode textureWrapMode)
{
    m_wrapMode = textureWrapMode;
}

void Texture::SetMinFilter(TextureFilter textureMinFilter)
{
    m_minFilter = textureMinFilter;
}

void Texture::SetMagFilter(TextureFilter textureMagFilter)
{
    m_magFilter = textureMagFilter;
}

void Texture::RequestMipmaps() {
    m_mipmapsRequested = true;
}

void Texture::SetLoadingState(LoadingState state) {
    m_loadingState = state;
}

const std::string& Texture::GetFileName() {
    return m_fileInfo.name;
}

int Texture::GetMipmapLevelCount() const {
    return m_mipmapLevelCount;
}

bool Texture::MipmapsAreRequested() const {
    return m_mipmapsRequested;
}

LoadingState Texture::GetLoadingState() const {
    return m_loadingState;
}

void Texture::PrintDebugInfo() {
    std::cout << GetFileName() << "\n";
    std::cout << " - mipmap level count: " << GetMipmapLevelCount() << "\n";
    std::cout << " - mipmaps requested: " << (MipmapsAreRequested() ? "TRUE" : "FALSE") << "\n";
    std::cout << "\n";
}