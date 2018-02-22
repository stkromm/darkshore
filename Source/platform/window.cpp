#include "platform/window.h"

#include <fstream>
#include <iostream>

#include "json.h"

using namespace platform;

static GLFWwindow* window;
static GLFWcursor* cursor;
static GLFWimage icons[2];

/**
Params:
title: String
icon: Path
cursor: Path
cursor_x: float
cursor_y: float
position_x: int
position_y: int
width: int
height: int
resolution_x: int
resolution_y: int
mode: int
*/
Window::Window() {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	std::ifstream config_file("config.json");
	json settings;
	if (config_file.is_open())
		config_file >> settings;
	else
		settings = {};

	if (settings["window"]["width"].is_number_integer())
		width = settings["window"]["width"];
	if (width == 0) width = 1024;

	if (settings["window"]["height"].is_number_integer())
		height = settings["window"]["height"];
	if (height == 0) height = 720;
	title = "";
	if (settings["window"]["title"].is_string())
	{
		std::stringstream title_stream;
		title_stream << settings["window"]["title"];
		title = title_stream.str().substr(1, title_stream.str().length() - 2);
	}
	if (title.length() == 0) title = "No title";

	//	Image icon = Image("res/image/icon.jpg");
	//	icons[0] = to_GLFW(icon);

	//	Image cursorIcon = Image("res/image/cursor.png");
	//	icons[1] = to_GLFW(cursorIcon);

	//	cursor = glfwCreateCursor(&icons[1], 0, 0);

	if (settings["window"]["mode"].is_number_integer())
	{
		switch ((int)settings["window"]["mode"]) {
		case FULLSCREEN:
			go_fullscreen();
		case BORDERLESS_WINDOWED:
			go_borderless();
		case WINDOWED:
			go_windowed();
		}
	}
	else {
		go_windowed();
	}
}

Window::~Window() {
	glfwDestroyWindow(window);
}

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

void WindowManager::shutdown() {
	glfwTerminate();
}

Window& WindowManager::get_window() {
	return *global_window;
}

void Window::update() {
	glfwPollEvents();
}

void glfwKeyCallback(GLFWwindow* w, const int key, const int action, const int c, const int d) {
	Window* window = static_cast<Window*>(glfwGetWindowUserPointer(w));
	if (!window) return;
	for (auto cb : window->keyCallbacks) {
		cb(key, action, c, d);
	}
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		window->close();
	}
}

void glfwCursorPositionCallback(GLFWwindow* w, const double x, const double y) {
	const Window* window = static_cast<Window*>(glfwGetWindowUserPointer(w));
	if (!window) return;
	for (const auto cb : window->cursorPositionCallbacks) {
		cb(x, y);
	}
}

void glfwMouseButtonCallback(GLFWwindow* w, const int a, const int b, const int c) {
	const Window* window = static_cast<Window*>(glfwGetWindowUserPointer(w));
	if (!window) return;
	for (const auto cb : window->mouseButtonCallbacks) {
		cb(a, b, c);
	}
}

void Window::close() {
	closed = true;
	glfwDestroyWindow(window);
}

void Window::resize(const uint32_t width, const uint32_t height) {
	glfwSetWindowSize(window, width, height);
}

void Window::set_clipboard_content(const char * content) const {
	glfwSetClipboardString(window, content);
}

const char* Window::get_clipboard_content() const {
	return glfwGetClipboardString(window);
}

const Screen& Window::get_screen() {
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	
	return 
		{width, height}
	;
}
void Window::recreate() {
	if (window) {
		glfwDestroyWindow(window);
	}
	window = glfwCreateWindow(width, height, title.c_str(), 0, window);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSetWindowPos(window, 0, 0);
	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window, glfwKeyCallback);
	glfwSetCursorPosCallback(window, glfwCursorPositionCallback);
	glfwSetMouseButtonCallback(window, glfwMouseButtonCallback);
	glfwSetCursor(window, cursor);
	glfwSetWindowIcon(window, 1, icons);

}

void Window::swap_buffers() const {
	glfwSwapBuffers(window);
}

void Window::go_windowed() {
	glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	recreate();
}

void Window::go_borderless() {

	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	if (mode) {
		width = mode->width;
		height = mode->height;
	}
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	recreate();
}

void Window::go_fullscreen()
{
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	if (mode) {
		width = mode->width;
		height = mode->height;
	}
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	recreate();
}

bool Window::should_close() const {
	return closed || glfwWindowShouldClose(window);
}
