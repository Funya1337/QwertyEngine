#include "Texture.h"

void Texture::Load()
{
    if (m_imageDataType == ImageDataType::UNCOMPRESSED) {
        m_textureDataLevels = { LoadUncompressedTextureData(m_fileInfo.path) };
        std::cout << "Uncompressed loading\n";
    }
    else if (m_imageDataType == ImageDataType::COMPRESSED) {
        std::cout << "Compressed loading\n";
    }
    else if (m_imageDataType == ImageDataType::EXR) {
        std::cout << "exr loading\n";
    }

    m_loadingState = LoadingState::LOADING_COMPLETE;
}

TextureData Texture::LoadUncompressedTextureData(const std::string& filePath)
{
    stbi_set_flip_vertically_on_load(true);
    TextureData textureData;
    uint8_t* imageData = stbi_load(filePath.data(), &textureData.m_width, &textureData.m_height, &textureData.m_channelCount, 0);
    if (imageData) {
        GLenum format = (textureData.m_channelCount == 4) ? GL_RGBA : GL_RGB;
        textureData.m_imageDataType = ImageDataType::UNCOMPRESSED;
        textureData.m_data = imageData;
        textureData.m_format = format;
        textureData.m_internalFormat = format;
    }
    else {
        std::cout << "Failed to load texture: " << filePath << std::endl;
    }
    //stbi_image_free(imageData);

    // Debug print
    std::cout << "Width:  " << textureData.m_width << '\n'
        << "Height: " << textureData.m_height << '\n'
        << "Channels: " << textureData.m_channelCount << '\n'
        << "Format: " << (textureData.m_format == GL_RGBA ? "GL_RGBA" : "GL_RGB") << '\n'
        << "Image type: " << "UNCOMPRESSED" << '\n'
        << "Data pointer: " << static_cast<void*>(textureData.m_data)
        << std::endl;
    return textureData;
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

OpenGLTexture& Texture::GetGLTexture() {
    return m_glTexture;
}

const ImageDataType Texture::GetImageDataType() {
    return m_imageDataType;
}

const TextureWrapMode Texture::GetTextureWrapMode() {
    return m_wrapMode;
}

const TextureFilter Texture::GetMinFilter() {
    return m_minFilter;
}

const TextureFilter Texture::GetMagFilter() {
    return m_magFilter;
}

const int Texture::GetFormat() {
    if (!m_textureDataLevels.empty()) {
        return m_textureDataLevels[0].m_format;
    }
    else {
        std::cout << "Texture::GetFormat() failed. m_textureData is empty\n";
        return 0;
    }
}

const int Texture::GetChannelCount() {
    if (!m_textureDataLevels.empty()) {
        return m_textureDataLevels[0].m_channelCount;
    }
    else {
        std::cout << "Texture::GetChannelCount() failed. m_textureData is empty\n";
        return 0;
    }
}
const int Texture::GetInternalFormat() {
    if (!m_textureDataLevels.empty()) {
        return m_textureDataLevels[0].m_internalFormat;
    }
    else {
        std::cout << "Texture::GetInternalFormat() failed. m_textureData is empty\n";
        return 0;
    }
}

const int Texture::GetWidth(int mipmapLevel) {
    if (mipmapLevel >= 0 && mipmapLevel < m_textureDataLevels.size()) {
        return m_textureDataLevels[mipmapLevel].m_width;
    }
    else {
        std::cout << "Texture::GetWidth(int mipmapLevel) failed. mipmapLevel '" << mipmapLevel << "' out of range of size " << m_textureDataLevels.size() << "\n";
        return 0;
    }
}

const int Texture::GetHeight(int mipmapLevel) {
    if (mipmapLevel >= 0 && mipmapLevel < m_textureDataLevels.size()) {
        return m_textureDataLevels[mipmapLevel].m_height;
    }
    else {
        std::cout << "Texture::GetHeight(int mipmapLevel) failed. mipmapLevel '" << mipmapLevel << "' out of range of size " << m_textureDataLevels.size() << "\n";
        return 0;
    }
}

TextureData* Texture::GetTextureDataLevel0()
{
    return &m_textureDataLevels[0];
}

void Texture::PrintDebugInfo() {
    std::cout << GetFileName() << "\n";
    std::cout << " - mipmap level count: " << GetMipmapLevelCount() << "\n";
    std::cout << " - mipmaps requested: " << (MipmapsAreRequested() ? "TRUE" : "FALSE") << "\n";
    std::cout << "\n";
}