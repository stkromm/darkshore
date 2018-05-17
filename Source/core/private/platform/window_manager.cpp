#include "core/platform/window_manager.h"

#include "core/platform/platform.h"
#include "core/logger/log.h"

using namespace platform;
static Window* global_window;

bool WindowManager::init()
{
	LOG_INFO << glfwGetVersionString() << LOG_END;
	if (!glfwInit())
	{
		LOG_INFO << "GLFW init failed" << LOG_END;
		return false;
	}
	global_window = new Window();

	return true;
}

Window& WindowManager::get_window()
{
	return *global_window;
}

void WindowManager::shutdown()
{
	glfwTerminate();
}
