#pragma once

#include <iostream>
#include "GL/glew.h"

namespace graphics
{
	/*
	By TheCherno Youtube OpenGL Series
	*/
#ifdef DEBUG 
#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

#else
#define GLCall(x) x
#define ASSERT(x) 
#endif

	void GLClearError();
	bool GLLogCall(const char* function, const char* file, int line);
}