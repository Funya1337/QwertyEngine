#include "GL_util.h"

namespace OpenGLUtil {
	GLint TextureWrapModeToGLEnum(TextureWrapMode wrapMode)
	{
		switch (wrapMode) {
			case TextureWrapMode::REPEAT: return GL_REPEAT;
			case TextureWrapMode::MIRRORED_REPEAT: return GL_MIRRORED_REPEAT;
			case TextureWrapMode::CLAMP_TO_EDGE: return GL_CLAMP_TO_EDGE;
			case TextureWrapMode::CLAMP_TO_BORDER: return GL_CLAMP_TO_BORDER;
			default: return GL_NONE;
		}
	}
	GLint TextureFilterToGLEnum(TextureFilter filter)
	{
		switch (filter) {
			case TextureFilter::NEAREST: return GL_NEAREST;
			case TextureFilter::LINEAR: return GL_LINEAR;
			case TextureFilter::LINEAR_MIPMAP: return GL_LINEAR_MIPMAP_LINEAR;
			default: return GL_NONE;
		}
	}
}