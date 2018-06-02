#include "platform/window.h"

#include <fstream>
#include <memory>

#include "platform/platform.h"
#include "core/json/json.h"
#include "platform/input.h"

using namespace ds::platform;

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
Window::Window()
{
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
		switch (int(settings["window"]["mode"]))
		{
		case FULLSCREEN:
			go_fullscreen();
		case BORDERLESS_WINDOWED:
			go_borderless();
		case WINDOWED:
			go_windowed();
		default:
			break;
		}
	}
	else
	{
		go_windowed();
	}
}

Window::~Window()
{
	glfwDestroyWindow(window);
}

Cursor Window::get_cursor() const
{
	float64 x;
	float64 y;
	glfwGetCursorPos(window, &x, &y);

	return { float(x), float(y) };
}

const Window* get_current_window(GLFWwindow* w)
{
	return static_cast<Window*>(glfwGetWindowUserPointer(w));
}

void on_resize(GLFWwindow* w, const int32 width, const int32 height)
{
	glViewport(0, 0, width, height);

	const Window* window = get_current_window(w);
	if (window)
	{
		for (const auto& callback_on_resize : window->windowResizeCallbacks)
		{
			callback_on_resize(width, height);
		}
	}
}

void Window::update() const
{
	glfwPollEvents();
}

void Window::poll_input() const
{
	glfwPollEvents();
}

void glfwKeyCallback(GLFWwindow* w, const int32 key, const int32 scancode, const int32 action, const int32 mods)
{
	if (action == GLFW_PRESS)
	{
		set_pressed(key, true);
	}
	else if (action == GLFW_RELEASE)
	{
		set_pressed(key, false);
	}
	auto window = static_cast<Window*>(glfwGetWindowUserPointer(w));
	if (!window) return;
	for (auto& cb : window->keyCallbacks)
	{
		cb(key, scancode, action, mods);
	}
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		window->close();
	}
	if (key == GLFW_KEY_F1 && action == GLFW_PRESS)
	{
		window->go_windowed();
	}
	if (key == GLFW_KEY_F2 && action == GLFW_PRESS)
	{
		window->go_fullscreen();
	}
	if (key == GLFW_KEY_F3 && action == GLFW_PRESS)
	{
		window->go_borderless();
	}
}

void glfwCursorPositionCallback(GLFWwindow* w, const float64 x, const float64 y)
{
	const Window* window = static_cast<Window*>(glfwGetWindowUserPointer(w));
	if (!window) return;
	for (const auto& cb : window->cursorPositionCallbacks)
	{
		cb(x, y);
	}
}

void glfwMouseButtonCallback(GLFWwindow* w, const int a, const int b, const int c)
{
	const Window* window = static_cast<Window*>(glfwGetWindowUserPointer(w));
	if (!window) return;
	for (const auto& cb : window->mouseButtonCallbacks)
	{
		cb(a, b, c);
	}
}

void Window::close()
{
	closed = true;
	glfwDestroyWindow(window);
}

void Window::resize(const uint32 width, const uint32 height) const
{
	glfwSetWindowSize(window, width, height);
}

void Window::set_clipboard_content(const char* content) const
{
	glfwSetClipboardString(window, content);
}

const char* Window::get_clipboard_content() const
{
	return glfwGetClipboardString(window);
}

Screen Window::get_screen() const
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);

	return { width, height };
}

void Window::create()
{
	if (!window)
	{
		window = glfwCreateWindow(width, height, title.c_str(), nullptr, window);
		glfwMakeContextCurrent(window);
		glfwSwapInterval(1);
		glfwSetWindowPos(window, 0, 0);
		glfwSetWindowUserPointer(window, this);
		glfwSetKeyCallback(window, glfwKeyCallback);
		glfwSetCursorPosCallback(window, glfwCursorPositionCallback);
		glfwSetMouseButtonCallback(window, glfwMouseButtonCallback);
		glfwSetCursor(window, cursor);
		glfwSetWindowIcon(window, 1, icons);
		glfwSetWindowSizeCallback(window, on_resize);
	}
	else
	{
		glfwSetWindowMonitor(window, glfwGetWindowMonitor(window), 0, 0, width, height, 60);
	}
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

}

void Window::swap_buffers() const
{
	glfwSwapBuffers(window);
}

void Window::go_windowed()
{
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	if (mode)
	{
		width = mode->width / 2;
		height = mode->height / 2;
	}
	glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	create();
}

void Window::go_borderless()
{
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	if (mode)
	{
		width = mode->width;
		height = mode->height;
	}
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	create();
}

void Window::go_fullscreen()
{
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	if (mode)
	{
		width = mode->width;
		height = mode->height;
	}
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	create();
}

bool Window::should_close() const
{
	return closed || glfwWindowShouldClose(window);
}

void Window::add_key_callback(const std::function<KeyCallback> keyCallback)
{
	keyCallbacks.push_back(keyCallback);
}

void Window::add_mouse_button_callback(const std::function<MouseButtonCallback> mouseButtonCallback)
{
	mouseButtonCallbacks.push_back(mouseButtonCallback);
}

void Window::add_cursor_position_callback(const std::function<CursorPositionCallback> cursorPositionCallback)
{
	cursorPositionCallbacks.push_back(cursorPositionCallback);
}

void Window::add_resize_callback(const std::function<WindowResizeCallback> resizeCallback)
{
	windowResizeCallbacks.push_back(resizeCallback);
}
