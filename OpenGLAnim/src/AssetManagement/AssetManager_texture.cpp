#include "AssetManager.h"
#include <stb/stb_image.h>
#include "../Utils/Util.h"

namespace AssetManager {


	void LoadPendingTexturesSync() {
		std::vector<Texture>& textures = getTextures();

		for (Texture& texture : textures) {
			if (texture.GetLoadingState() == LoadingState::AWAITING_LOADING_FROM_DISK) {
				texture.SetLoadingState(LoadingState::LOADING_FROM_DISK);
				LoadTexture(&texture);
			}
		}
	}

	void LoadPendingTexturesAsync() {
		// TODO
		std::cout << "texture loading async\n";
	}

	void LoadTexture(Texture* texture) {
		if (texture) {
			texture->Load();
		}
	}

	//GLuint LoadTexture(const std::string& path) {

	//	GLuint textureID;
	//	glGenTextures(1, &textureID);
	//	glBindTexture(GL_TEXTURE_2D, textureID);

	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//	stbi_set_flip_vertically_on_load(true);
	//	int width, height, nrChannels;
	//	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	//	if (data) {
	//		GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
	//		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	//		glGenerateMipmap(GL_TEXTURE_2D);
	//	}
	//	else {
	//		std::cout << "Failed to load texture: " << path << std::endl;
	//	}
	//	stbi_image_free(data);

	//	return textureID;
	//}
}