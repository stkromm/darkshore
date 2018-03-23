#pragma once
#include "graphics/graphics.h"

namespace graphics
{
	namespace RenderManager
	{
		inline bool init()
		{
			if (glewInit() != GLEW_OK)
			{
				std::cout << "GLEW init failed" << std::endl;
				return false;
			}

			std::cout << glGetString(GL_VERSION) << std::endl;
			std::cout << glGetString(GL_VENDOR) << std::endl;
			std::cout << glGetString(GL_RENDERER) << std::endl;
			std::cout << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

			return true;
		}

		inline void shutdown()
		{
		}
	};
};
