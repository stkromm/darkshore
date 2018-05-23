#pragma once

// ReSharper disable once CppUnusedIncludeDirective
#include "third_party/gl/glew.h"
#include "core/logger/log.h"
#include "core/types.h"

namespace ds {
	namespace graphics
	{
		/*
		By TheCherno Youtube OpenGL Series
		*/
#ifdef DEBUG 
#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) x;

#else
#define GLCall(x) x;
#define ASSERT(x) 
#endif

		inline void GLAPIENTRY
			MessageCallback(GLenum source,
				GLenum type,
				GLuint id,
				GLenum severity,
				GLsizei length,
				const GLchar* message,
				const void* userParam)
		{
			LOG_INFO << "GL:: " << message << LOG_END;
		}

		inline bool init()
		{
			const uint32 error = glewInit();
			if (error)
			{
				LOG_INFO << "GLEW init failed " << glewGetErrorString(error) << LOG_END;
				return false;
			}

			LOG_INFO << glGetString(GL_VERSION) << LOG_END;
			LOG_INFO << glGetString(GL_VENDOR) << LOG_END;
			LOG_INFO << glGetString(GL_RENDERER) << LOG_END;
			LOG_INFO << glGetString(GL_SHADING_LANGUAGE_VERSION) << LOG_END;

			glEnable(GL_DEBUG_OUTPUT);
			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_LOW, 0, nullptr, GL_TRUE);
			glDebugMessageCallback(MessageCallback, nullptr);

			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			return true;
		}
	}
}
