#include "graphics/graphics.h"

namespace graphics
{
	void GLClearError()
	{
		while (glGetError() != GL_NO_ERROR)
		{
		}
	}

	bool GLLogCall(const char* function, const char* file, const int line)
	{
		while (const GLenum error = glGetError())
		{
			std::cout << "[OpenGL Error] :" << error << " function:" << function << " file:" << file << " line:" << line << std::
				endl;
			return false;
		}
		return true;
	}
}
