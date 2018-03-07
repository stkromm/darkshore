#include "platform/window_manager.h"

#include <iostream>

using namespace platform;
static Window* global_window;

bool WindowManager::init() {
	std::cout << glfwGetVersionString() << std::endl;
	if (!glfwInit()) {

		std::cout << "GLFW init failed" << std::endl;
		return false;
	}
	else {
		global_window = new Window();

		return true;
	}
}

Window& WindowManager::get_window() {
	return *global_window;
}

void WindowManager::shutdown() {
	glfwTerminate();
}