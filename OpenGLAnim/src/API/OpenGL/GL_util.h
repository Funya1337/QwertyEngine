#pragma once
#include <glad/glad.h>
#include "../../Common/QwertyTypes.h"

namespace OpenGLUtil {
	GLint TextureWrapModeToGLEnum(TextureWrapMode wrapMode);
	GLint TextureFilterToGLEnum(TextureFilter filter);
}